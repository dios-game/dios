#include "precompiled.h"
#include "util_charset_utf8.h"

NS_DS_BEGIN
NS_UTIL_BEGIN

std::wstring CCharsetUTF8::s2ws( const std::string& str )
{
	if(str.empty()) {
		return L"";
	}

	int size_s = str.size();
	int size_d = size_s + 10;        

	wchar_t *des = new wchar_t[size_d];
	memset(des, 0, size_d * sizeof(wchar_t));

	int s = 0, d = 0;
	bool toomuchbyte = true; //set true to skip error prefix.

	while (s < size_s && d < size_d) {

		unsigned char c = str[s];
		if ((c & 0x80) == 0) {
			des[d++] += str[s++];
		}
		///< 110x-xxxx 10xx-xxxx 
		else if((c & 0xE0) == 0xC0) {

			wchar_t &wideChar = des[d++];
			wideChar  = (str[s + 0] & 0x3F) << 6;
			wideChar |= (str[s + 1] & 0x3F);

			s += 2;
		}
		///< 1110-xxxx 10xx-xxxx 10xx-xxxx
		else if((c & 0xF0) == 0xE0) {

			wchar_t &wideChar = des[d++];
			wideChar  = (str[s + 0] & 0x1F) << 12;
			wideChar |= (str[s + 1] & 0x3F) << 6;
			wideChar |= (str[s + 2] & 0x3F);

			s += 3;
		} 
		///< 1111-0xxx 10xx-xxxx 10xx-xxxx 10xx-xxxx 
		else if((c & 0xF8) == 0xF0) {

			wchar_t &wideChar = des[d++];
			wideChar  = (str[s + 0] & 0x0F) << 18;
			wideChar  = (str[s + 1] & 0x3F) << 12;
			wideChar |= (str[s + 2] & 0x3F) << 6;
			wideChar |= (str[s + 3] & 0x3F);

			s += 4;
		} 
		///< 1111-10xx 10xx-xxxx 10xx-xxxx 10xx-xxxx 10xx-xxxx 
		else {

			wchar_t &wideChar = des[d++]; 
			wideChar  = (str[s + 0] & 0x07) << 24;
			wideChar  = (str[s + 1] & 0x3F) << 18;
			wideChar  = (str[s + 2] & 0x3F) << 12;
			wideChar |= (str[s + 3] & 0x3F) << 6;
			wideChar |= (str[s + 4] & 0x3F);

			s += 5;
		}
	}

	std::wstring t = des;
	delete[] des;
	des = 0;

	return t;
}

std::string CCharsetUTF8::ws2s( const std::wstring& str )
{
	char utf8[4096];

	int len = 0;
	int size_d = 4096;

	for (std::wstring::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		wchar_t wchar = *it;
		if (wchar < 0x80) {

			//length = 1;
			utf8[len++] = (char)wchar;
		}
		else if(wchar < 0x800) {

			if (len + 1 >= size_d) {
				return "";
			}

			utf8[len++] = 0xc0 | ( wchar >> 6 );
			utf8[len++] = 0x80 | ( wchar & 0x3f );
		}
		else if(wchar < 0x10000 ) {

			//length = 3;
			if (len + 2 >= size_d) {
				return "";
			}

			utf8[len++] = 0xe0 | ( wchar >> 12 );
			utf8[len++] = 0x80 | ( (wchar >> 6) & 0x3f );
			utf8[len++] = 0x80 | ( wchar & 0x3f );
		}
		else if( wchar < 0x200000 ) {

			//length = 4;
			if (len + 3 >= size_d) {
				return "";
			}

			utf8[len++] = 0xf0 | ( (int)wchar >> 18 );
			utf8[len++] = 0x80 | ( (wchar >> 12) & 0x3f );
			utf8[len++] = 0x80 | ( (wchar >> 6) & 0x3f );
			utf8[len++] = 0x80 | ( wchar & 0x3f );
		}
	}
	return std::string(utf8, len);
}

size_t CCharsetUTF8::VerifyUTF8( const std::string& str )
{
	std::string::const_iterator i, ie = str.end();
	i = str.begin();
	size_t length = 0;

	while ( i != ie ) {

		// characters pass until we find an extended sequence
		if (( *i ) & 0x80 ) {

			unsigned char c = ( *i );
			size_t contBytes = 0;

			// get continuation byte count and test for overlong sequences
			if (( c & ~_lead1_mask ) == _lead1 ) { // 1 additional byte
				if ( c == _lead1 ) {
					//throw invalid_data( "overlong UTF-8 sequence" );
					return str.size();
				}
				contBytes = 1;

			} else if (( c & ~_lead2_mask ) == _lead2 ) { // 2 additional bytes
				contBytes = 2;
				if ( c == _lead2 ) { // possible overlong UTF-8 sequence
					c = ( *( i + 1 ) ); // look ahead to next byte in sequence
					if (( c & _lead2 ) == _cont ) {
						//throw invalid_data( "overlong UTF-8 sequence" );
						return str.size();
					}
				}

			} else if (( c & ~_lead3_mask ) == _lead3 ) { // 3 additional bytes
				contBytes = 3;
				if ( c == _lead3 ) { // possible overlong UTF-8 sequence
					c = ( *( i + 1 ) ); // look ahead to next byte in sequence
					if (( c & _lead3 ) == _cont ) {
						//throw invalid_data( "overlong UTF-8 sequence" );
						return str.size();
					}
				}

			} else if (( c & ~_lead4_mask ) == _lead4 ) { // 4 additional bytes
				contBytes = 4;
				if ( c == _lead4 ) { // possible overlong UTF-8 sequence
					c = ( *( i + 1 ) ); // look ahead to next byte in sequence
					if (( c & _lead4 ) == _cont ) {
						//throw invalid_data( "overlong UTF-8 sequence" );
						return str.size();
					}
				}

			} else if (( c & ~_lead5_mask ) == _lead5 ) { // 5 additional bytes
				contBytes = 5;
				if ( c == _lead5 ) { // possible overlong UTF-8 sequence
					c = ( *( i + 1 ) ); // look ahead to next byte in sequence
					if (( c & _lead5 ) == _cont ) {
						//throw invalid_data( "overlong UTF-8 sequence" );
						return str.size();
					}
				}
			}

			// check remaining continuation bytes for
			while ( contBytes-- ) {
				c = ( *( ++i ) ); // get next byte in sequence
				if (( c & ~_cont_mask ) != _cont ) {
					//throw invalid_data( "bad UTF-8 continuation byte" );
					return str.size();
				}
			}
		}
		length++;
		i++;
	}
	return length;
}

NS_UTIL_END
NS_DS_END
