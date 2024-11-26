return {
	Update = function()
		print("[LUA] Updating")
		print(entity)
		print(entity:has_component(2))
		print(get_dt())
	end,
}
