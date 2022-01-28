uniform sampler2D texture;
varying vec2 v_texCoord;

uniform lowp vec4 tone;

const vec3 lumaF = vec3(.299, .587, .114);

void main() {
    /* Sample source color */
	vec4 frag = texture2D(texture, v_texCoord);
	
	/* Apply gray */
	float luma = dot(frag.rgb, lumaF);
	frag.rgb = mix(frag.rgb, vec3(luma), tone.w);
	
	/* Apply tone */
	frag.rgb += tone.rgb;

    /* Finalize shader */
    gl_FragColor = frag;
}