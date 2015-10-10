#include "precompiled.h"
#include "util_boost_uuid.h"

NS_DS_BEGIN
NS_UTIL_BOOST_BEGIN

static boost::thread_specific_ptr<boost::uuids::random_generator> random_gen_tls;
static boost::thread_specific_ptr<boost::uuids::string_generator> string_gen_tls;
static boost::thread_specific_ptr<boost::uuids::nil_generator> nil_gen_tls;

boost::uuids::uuid CUuid::CreateUuid( void )
{
	boost::uuids::random_generator* gen = random_gen_tls.get();
	if(!gen) {
		gen = new boost::uuids::random_generator;
		random_gen_tls.reset(gen);
	}
	return (*gen)();
}

boost::uuids::uuid CUuid::CreateUuid( const std::string& str )
{
	boost::uuids::string_generator* gen = string_gen_tls.get();
	if(!gen) {
		gen = new boost::uuids::string_generator;
		string_gen_tls.reset(gen);
	}
	return (*gen)(str);
}

boost::uuids::uuid CUuid::CreateNilUuid( void )
{
	boost::uuids::nil_generator* gen = nil_gen_tls.get();
	if(!gen) {
		gen = new boost::uuids::nil_generator;
		nil_gen_tls.reset(gen);
	}
	return (*gen)();
}

NS_UTIL_BOOST_END
NS_DS_END
