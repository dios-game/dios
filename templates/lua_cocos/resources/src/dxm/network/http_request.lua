

dxm.CHttpRequest = class("game.CHttpRequest")
local CHttpRequest = dxm.CHttpRequest

--[[
    request:
        url .. action ..".php?" .. param
    response:
        {
            "code":1,
            "data":{},
            "action_data":{}
        }
]]--

function CHttpRequest:ctor(user)
    self.requesting = false;
end

function CHttpRequest:Request(url, action, param, response_callback)

    if self.requesting==true then
        return
    end

    -- �½�һ��XMLHttpRequest����
    local xhr = cc.XMLHttpRequest:new()
    -- json��������
    xhr.responseType = cc.XMLHTTPREQUEST_RESPONSE_JSON
    -- GET��ʽ
    xhr:open("GET", url .. action ..".php?" .. param)

    local function onReadyStateChange()

        -- �������;
        self.requesting = false
        if self.request_done_callback ~= nil then
            self.request_done_callback()
        end

        -- ��ʾ״̬��,�ɹ���ʾ200
        if xhr.status == 200 then
            local response = xhr.response
            -- �����Ӧ����
            local response_json = json.decode(response, 1)

            -- ������
            if response_json == nil then
                -- ���������
                response_callback( -1 )
                return
            end

            --[[ ���� code ��Ϊ 0 ����� ]]
            if response_json.code ~= 0 then
                response_callback(response_json.code)
                return false
            end

            -- ��������
            local data = response_json["data"] or {}
            -- self:_SaveData(response_json)

            -- ��Ӧ��
            local action_data = response_json["action_data"] or {}
            response_callback(0, action_data)
        else
            -- ״̬��Ϊ200
            -- self:_OpenRewardPanel("status is error code[" .. xhr.status .. "]")
            response_callback( -xhr.status )
        end
    end

    -- ע��ű������ص�
    xhr:registerScriptHandler(onReadyStateChange)
    -- ��������
    xhr:send()

    if self.request_waitting_callback ~= nil then
        self.request_waitting_callback()
    end
    self.requesting = true
end

function CHttpRequest:_SaveData(result)

    if type(result) ~= "table" then return end

    --[[
    if isset(result, "user") then
        self.user.data.user = result.user
    end
    if isset(result, "trees") then
        self.user.data.trees = result.trees
    end
    if isset(result, "reward_history") then
        self.user.data.reward_history = result.reward_history
    end
    if isset(result, "bag") then
        self.user.data.bag = result.bag
    end
    if isset(result, "sign_in") then
        self.user.data.sign_in = result.sign_in
    end
    --]]
end

function CHttpRequest:SetRequestWaitingCallback(callback)
    self.request_waitting_callback = callback
end

function CHttpRequest:SetRequestDoneCallback(callback)
    self.request_done_callback = callback
end

return CHttpRequest