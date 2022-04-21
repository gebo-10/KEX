require("fun")
function log( ... )
	print("Lua:",...)
end
function Error(e)
	log("eeeee",e)
end
function Init()
	log("Lua Init",os.clock ())
	fun()
	myfun()
end

function Init2()
	log("Lua Init",e+1)
end
log("xxx")
--a=xx+1