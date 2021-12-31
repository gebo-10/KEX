require("lib.fun")
function log( ... )
	print("Lua:",...)
end
function Init()
	log("Lua Init")
	local c=Color.new(0.1,0.2,0.3)
	log(c.r,c.g,c.b,c.a)
	local rectf = Rectf.new(1,2,3,4);
	log(rectf.x,rectf.y,rectf.w,rectf.h)
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