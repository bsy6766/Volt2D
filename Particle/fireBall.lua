particleSystem = {
	name = "fireBall",
	pause = false,
	blend = true,
	size = 350,
	duration = 10,

	posVar = {
		x = 0,
		y = 0,
		z = 0
	},

	startColor = {
		r = 193.8,
		g = 63.75,
		b = 30.6,
		a = 255
	},
	startColorVar = {
		r = 0,
		g = 0,
		b = 0,
		a = 0
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

	speed = 20,
	speedVar = 5,

	gravityX = 0,
	gravityY = 0,

	tanAccel = 0,
	tanAccelVar = 0,

	radialAccel = 0,
	radialAccelVar = 0,

	emitAngle = 90,
	emitAngleVar = 360,

	startSize = 60,
	startSizeVar = 10,

	endSize = 1,
	endSizeVar = 0,

	startAngle = 0,
	startAngleVar = 0,

	endAngle = 0,
	endAngleVar = 0,

	lifeTime = 1,
	lifeTimeVar = 0.5,
	-- textureName = "default_particle.png"
	textureName = "default_blur_circle_particle.png"
}