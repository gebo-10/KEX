--require("lib.fun")

function log( ... )
	print("Lua:",...)
end

-- function haha(a)
-- 	return a+2;
-- end

function Init()
	log("Lua Init")
	local c=kengine.Color.new(0.1,0.2,0.3)
	log(c.r,c.g,c.b,c.a)
	local rectf = kengine.Rectf.new(1,2,3,4);
	log(rectf.x,rectf.y,rectf.w,rectf.h)
	--test({tttt=c})
	for k,v in pairs(_G) do
		print(k,v)
	end

	for k,v in pairs(kengine) do
		print(k,v)
	end
end

function Update()
	--fun()
	--print("lua update",a+b)
end

function OnEvent(event)
	-- body
end

function OnError(str)
	print(str)
end