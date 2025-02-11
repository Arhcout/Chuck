return {
	Update = function()
		local pos = get_mouse_pos()
		entity:transform_set_position(pos.x, pos.y)
	end,
}
