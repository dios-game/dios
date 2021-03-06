--region *.lua
--Date
--此文件由[BabeLua]插件自动生成
require "cocos.init"

cc.exports.dxm = cc.exports.dxm or {}

require "dxm/common/singleton"
require "dxm/common/time_helper"
require "dxm/common/simple_db"

require "dxm/network/http_request"

require "dxm/scene/base_scene"
require "dxm/ui/normal_ui.lua"
require "dxm/ui/stack_ui.lua"
require "dxm/ui/dialog_ui"
require "dxm/ui/scroll_view_ui.lua"

-- 本地数据
dxm.CSimpleDB.Init("game_state")
dxm.CSimpleDB.Load()

--endregion
