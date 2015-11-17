

dxm.CSimpleDB = { }

local CSimpleDB = dxm.CSimpleDB

local db_file_name = "simple_db.txt"
local event_listener = nil
local secret_key = nil

----------------------------------------
function CSimpleDB.Init(db_file_name)
    if type(db_file_name) == "string" then
        db_file_name = db_file_name
    end
    return true
end

function CSimpleDB.Load()
    local filename = CSimpleDB.GetCSimpleDBPath()
    dxm.CSimpleDB.data = {}
    if not io.exists(filename) then
        return
    end

    local contents = io.readfile(filename)
    local values = json.decode(contents)
    if type(values) ~= "table" then
        return
    end

    dxm.CSimpleDB.data = values
end

function CSimpleDB.Save()
    local values = dxm.CSimpleDB.data
    if type(values) ~= "table" then
        return false
    end

    local filename = CSimpleDB.GetCSimpleDBPath()
    local ret = false
    local s = json.encode(values)
    if type(s) == "string" then
        ret = io.writefile(filename, s)
    end
    return ret
end

function CSimpleDB.GetCSimpleDBPath()
    return string.gsub(device.writablePath, "[\\\\/]+$", "") .. device.directorySeparator .. db_file_name
end

return CSimpleDB
