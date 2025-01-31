local x = 0;
math = require("math")
return {
	Update = function()
		print("[LUA] Updating")
		print(entity)
		print(entity:has_component(2))
		local dt = get_dt()
		x = x + dt * 30
		print(x)
		entity:transform_set_position(x, 100)
		entity:transform_set_rotation(x)
		entity:transform_set_scale(math.sin(x / 30), math.cos(x / 30))
	end,
}
