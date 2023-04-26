/*
 * ----------------------------------------------------------------------------
 * "THE MODIFIED BEER-WARE LICENSE" (Revision 1):
 * <zmey20000@yahoo.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Mikhail E. Zakharov
 * ----------------------------------------------------------------------------
 */

#include "libastral.h"

#include <stdio.h>

int main() {
	struct portal *p;
	unsigned char voice_divine[STATEMENT_MAX_LENGTH];

	p = astral_open();

/*	p->v_style = VOICE_STYLE_SIMPLE; */
	p->v_style = VOICE_STYLE_BIBLE;
	astral_listen(p, voice_divine);

	printf("%s", voice_divine);

	astral_close(p);
}

