
uniform sampler2D selfsprite;

void main(){

	vec4 col = texture2D(selfsprite, gl_TexCoord[0].xy);
	
	vec2 XY = vec2(300, 1600);

	XY = gl_FragCoord - XY;
	float radius = abs(sqrt(XY.x * XY.x + XY.y * XY.y));

	if(radius > 200)
		radius = 0;
	else{
		radius = 200 - radius;
		radius = 0.005f * radius;
	}

	col.y += radius * 0.1f;

	col.x -= radius * 0.5f;

	gl_FragColor = vec4(clamp(col, 0.0, 1.0));
}