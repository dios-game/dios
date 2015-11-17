--region NewFile_1.lua
--Author : IBM
--Date   : 2015/4/27
--此文件由[BabeLua]插件自动生成

require("dxm/ui/base_ui")

dxm = dxm or {}
dxm.CLayerUI = class("CLayerUI", dxm.CBaseUI)

local CLayerUI = dxm.CLayerUI

function CLayerUI:ctor()
    CLayerUI.super.ctor(self)
end

function CLayerUI:Dispose()
    self:_ClearUI()

    if self.layer ~= nil then
        self.layer:release()
    end
end

function CLayerUI:Init()
    if CLayerUI.super.Init(self) == false then
        return false
    end
    self.layer = display.newLayer()
    if self.layer ~= nil then
        self.layer:retain()
        self.layer:addChild(self.widget)
        self.layer:onKeypad(function(event) cc.Director:getInstance():endToLua() end)
    end
    return true
end

-- 成员函数
function CLayerUI:Create()
    local layer_ui = CLayerUI.new()
    layer_ui:Init()
    return layer_ui
end

function CLayerUI:AttachParent(parent)
    parent:addChild(self.layer)
	self:_Enter()
end

function CLayerUI:DetachParent()
    self:_Exit()
    self.layer:removeFromParent()
end

return CLayerUI

--endregion
