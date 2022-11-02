function functions(List)
    add_function(List,"LuaGetBody")
    add_function(List,"LuaGetKey")
    add_function(List,"LuaPutMsg")
    add_function(List,"LuaPutLog")
    add_function(List,"LuaStrlen")
end

function test(Kmsg,Node)
    key = LuaGetKey(Kmsg)
    if(key=="temperature")
    then
        body = LuaGetBody(Kmsg)
        LuaPutLog(Node,"body : " .. body)
        if(tonumber(body)>=100)
        then
            LuaPutMsg(Node,"/alarms/fire", 12, "temperature is too high", 23, body, LuaStrlen(body))
        end
    end
end