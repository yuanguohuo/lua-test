package.cpath="../../lua-call-c/?.so;;"

w = require "libwatermelon"

width = 100.5
hight = 200.8

background = { r = 0.5, g = 0.5, b = 0.5}
forground = { r = 1, g = 0, b = 0}

function add(x,y)
	local list=w.watermelondir("/home")
	for i,j in ipairs(list) do
		print(i, j);
	end

	local ret=w.watermelonsin(3.1415926/4)
	print(ret)

	return x+y
end


