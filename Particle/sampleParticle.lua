-- table name must be "particelSystem"
particleSystem = {
	-- Name of object (optional)
	name = "testParticle",
	-- True to pause particle system on creation. False to run right away.
	pause = true,
	-- blending. True to blend each particles betwen. False to render base on depth
	blend = true,
	-- Size of particles 
	size = 500,
	-- Duration of particle system. -1 means infinite repeat
	duration = 20,
	-- Particle's spawning position variantion. 
	-- System's position is used for base spawning position.
	-- Variation can not be greater than screen size. (origin in center of screen)
	posVar = {
		x = 0,
		y = 0,
		z = 0
	},
	-- Starting color with RGBA. 
	-- Each color value can have 0 to 255.0
	startColor = {
		r = 127,
		g = 127,
		b = 127,
		a = 255
	},
	-- Starting color variation. 
	-- Each color value can have 0 to 255.0
	startColorVar = {
		r = 127,
		g = 127,
		b = 127,
		a = 127 
	},
	-- Ending color. Same as starting color.
	-- Each color value can have 0 to 255.0
	endColor = {
		r = 0,
		g = 0,
		b = 0,
		a = 255
	},
	-- Ending color variation.
	-- Each color value can have 0 to 255.0
	endColorVar = {
		r = 0,
		g = 0,
		b = 0,
		a = 0
	},
	-- True to apply above color setting to particle texture. Else, false.
	applyColor = true,
	-- Base speed for each particles. 
	-- Min = 0, Max = 1000
	speed = 10,
	-- Speed variation
	-- Min = 0, Max = 1000
	speedVar = 0,
	-- Gravity toward x coordinates.
	-- Positive value applies gravity left to right, vice versa. 
	-- Min = -3000, Max = 3000
	gravityX = 0,
	-- Gravity toward y coordinates.
	-- Positive value applies gravity top to bottom, vice versa. 
	-- Min = -3000, Max = 3000
	gravityY = 0,
	-- Tangential acceleration.
	-- Power applies to perpendicular direction of particle's moving direction
	-- Min = -1000, Max = 1000
	tanAccel = 0,
	-- Tengential acceleration variance.
	-- Min = -1000, Max = 1000
	tanAccelVar = 0,
	-- Radial acceleration.
	-- Power applies toward or away from each particle's spawning point.
	-- Positive value pushes away from, negtive value pulls toward to spawning point.
	-- Min = -1000, Max = 1000
	radialAccel = 0,
	-- Radial acceleration variance
	-- Min = -1000, Max = 1000
	radialAccelVar = 0,
	-- Particle's emission angle in degree.
	-- 0 starts from east. Rotates clockwise. 90 degree will point north.
	-- Min = 0, Max = 360
	emitAngle = 0,
	-- Emission angle variance.
	-- Min = 0, Max = 360
	emitAngleVar = 0,
	-- Starting size of particle.
	-- 0 is smallest size you can set and particles with 0 sized will not be rendered on screen.
	-- 128 is the largest size you can set and particles will be rendered twice big as original size.
	-- Default particle textures have 256 pixels for both width and height.
	-- Setting 128 will render particles with original size.
	-- However, particles can be scaled twice big by variance.
	-- Min = 0, Max = 128
	startSize = 128,
	-- Variance for starting size
	-- Min = 0, Max = 128
	startSizeVar = 0,
	-- Ending size of particle. Same as starting size.
	-- Set -1 to make same size with start size.
	-- Min = 0, Max = 128
	endSize = -1,
	-- Variance for ending size
	-- Min = 0, Max = 128
	endSizeVar = 0,
	-- Starting angle. 
	-- Min = -3600, Max = 3600
	startAngle = 0,
	-- Starting angle variance
	-- Min = 0, Max = 3600
	startAngleVar = 0,
	-- Ending angle
	-- Min = -3600, Max = 3600
	endAngle = 0,
	-- Ending angle variance
	-- Min = 0, Max = 3600
	endAngleVar = 0,
	-- Time for each particle's life. 
	-- Stops rendering if each particle's lived time exceeds its' life time.
	-- Can live up to 60 seconds(1 minute) with variance.
	-- Min = 0, Max = 30
	lifeTime = 4,
	-- Life time variance. 
	-- Min = 0, Max = 30
	lifeTimeVar = 1,
	-- Name of texture.
	textureName = "default_blur_circle_particle.png"
}







