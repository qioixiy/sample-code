#extension GL_OES_standard_derivatives : enable
precision mediump float;

varying vec2 v_texCoord;

// distance to a line (can't get simpler than this)
float line(vec2 a, vec2 b, vec2 p )
{
	vec2 pa = p - a;
	vec2 ba = b - a;
	float h = clamp( dot(pa,ba)/dot(ba,ba), 0.0, 1.0 );
	return length( pa - ba*h );
}

void main() {
	vec2 iResolution = vec2(600., 300.);
	float iGlobalTime = 20.0;
    vec2 _fragCoord = vec2(300., 300.);
    _fragCoord = v_texCoord;	
	vec2 p = (-iResolution.xy + 900.0*_fragCoord.xy) / iResolution.yy;
	vec2 q = p;
	
	vec2 c = vec2(0.0);
	
    // background	
	vec3 col = vec3(0.5,0.85,0.9)*(1.0-0.2*length(p));
	if( q.x>c.x && q.y>c.y ) col = pow(col,vec3(2.2));

    // zoom in and out	
	p *= 1.0 + 0.2*sin(iGlobalTime*0.4);
	
	
	// compute distance to a set of lines
    float d = 1e20;	
	for( int i=0; i<7; i++ )
	{
        float anA = 6.2831*float(i+0)/7.0 + 0.15*iGlobalTime;
        float anB = 6.2831*float(i+3)/7.0 + 0.20*iGlobalTime;
		vec2 pA = 0.95*vec2( cos(anA), sin(anA) );		
        vec2 pB = 0.95*vec2( cos(anB), sin(anB) );		
		float h = line( pA, pB, p );
		d = min( d, h );
	}

    // lines/start, left side of screen	: not filtered
	if( q.x<c.x )
	{
		if( d<0.12 ) col = vec3(0.0,0.0,0.0); // black 
		if( d<0.04 ) col = vec3(1.0,0.6,0.0); // orange
	}
    // lines/start, right side of the screen: filtered
	else
	{
		float w = 0.5*fwidth(d); 
		w *= 1.5; // extra blur
		
		if( q.y<c.y )
		{
		col = mix( vec3(0.0,0.0,0.0), col, smoothstep(-w,w,d-0.12) ); // black
		col = mix( vec3(1.0,0.6,0.0), col, smoothstep(-w,w,d-0.04) ); // orange
		}
		else
		{
		col = mix( pow(vec3(0.0,0.0,0.0),vec3(2.2)), col, smoothstep(-w,w,d-0.12) ); // black
		col = mix( pow(vec3(1.0,0.6,0.0),vec3(2.2)), col, smoothstep(-w,w,d-0.04) ); // orange
		}
	}

	if( q.x>c.x && q.y>c.y )
		col = pow( col, vec3(1.0/2.2) );
	
    // draw left/right separating line
	col = mix( vec3(0.0), col, smoothstep(0.007,0.008,abs(q.x-c.x)) );
	col = mix( col, vec3(0.0), (1.0-smoothstep(0.007,0.008,abs(q.y-c.y)))*step(0.0,q.x-c.x) );
	
	gl_FragColor = vec4( col, 1.0 );
}
