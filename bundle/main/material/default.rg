local pass1={
	input={
		texture={
			type=Texture,
			id="texture1",
		},
		ubo={
			{
				bind=0,
				value={0,0,0}
			}
		},
		ssbo={
			{
				bind=0,
				value={0,0,0}
			}
		}
	},
	material={
		file="test.mg",
	}
	target="target1";
	
}
local pass2={
	camera_id=0,
}
local RenderGraph={
	resource={
		texture1={
			type=Texture,
			file="",
			bind=0,
			-- width=64;
			-- height=64;
			data_type=TextureDataType::UNSIGNED_BYTE,--5121
			data_format=TextureDataFormat::RGBA,
			internal_format=TextureInternalFormat::RGBA,
			min_filter=TextureFilterMode::LINEAR,
			mag_filter=TextureFilterMode::LINEAR,
			s_warp = TextureWarpMode::CLAMP_TO_EDGE,
			r_warp = TextureWarpMode::CLAMP_TO_EDGE,
			t_warp = TextureWarpMode::CLAMP_TO_EDGE,
		},
		target1={
			width=100,
			height=100,
			component={
				{
					type="rbo",
				},
				{
					type="render_texture",
				},
				{
					type="texture",
				},
			}
		}
	},
	pass={
		pass1,
		pass2,
	}
}

return RenderGraph