particleSystem = {
	name = "blueMeteor",
	blend = true,
	size = 500,
	duration = 10,

	posVar = {
		x = 0,
		y = 0,
		z = 0
	},

	startColor = {
		r = 0,
		g = 131,
		b = 242,
		a = 255
	},
	startColorVar = {
		r = 0,
		g = 0,
		b = 5,
		a = 1
	},

	endColor = {
		r = 0,
		g = 0,
		b = 0,
		a = 255
	},
	endColorVar = {
		r = 0,
		g = 0,
		b = 0,
		a = 0
	},

	applyColor = true,

	speed = 25,
	speedVar = 5,

	gravityX = -200,
	gravityY = 200,

	tanAccel = 0,
	tanAccelVar = 0,

	radialAccel = 0,
	radialAccelVar = 0,

	emitAngle = 90,
	emitAngleVar = 360,

	startSize = 100,
	startSizeVar = 10,

	endSize = 0,
	endSizeVar = 0,

	startAngle = 0,
	startAngleVar = 0,

	endAngle = 0,
	endAngleVar = 0,

	lifeTime = 1.5,
	lifeTimeVar = 0.5,
	-- textureName = "default_particle.png"
	textureName = "default_star_particle.png"
}