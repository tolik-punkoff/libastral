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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define version	"libastral-0.5"

/* -------------------------------------------------------------------------- */
struct portal* astral_open() {
	struct portal *p;

	p = (struct portal *)malloc(sizeof(struct portal));

	if ((p->gate = open("/dev/urandom", O_RDONLY)) == -1) {
		fprintf(stderr, "astral_open() failed\n");
		free(p);
		exit(1);
	}

	/* init portal values */
	p->l_min = LETTERS_MIN;
	p->l_max = LETTERS_MAX;
	p->w_min = WORDS_MIN;
	p->w_max = WORDS_MAX;
	p->s_min = SENTANCES_MIN;
	p->s_max = SENTANCES_MAX;
	p->p_min = PARAGRAPHS_MIN;
	p->p_max = PARAGRAPHS_MAX;
	p->w_style = WORD_STYLE_SIMPLE;
	p->s_style = SENTANCE_STYLE_SIMPLE;
	p->v_style = VOICE_STYLE_BIBLE;
	p->st_bible_lnlen = VOICE_STYLE_BIBLE_LNLEN;

	return p;
}

/* -------------------------------------------------------------------------- */
int astral_close(struct portal *p) {
	if (close(p->gate) == -1) {
		fprintf(stderr, "astral_close() failed\n");
		free(p);
		exit(1);
	}

	free(p);
	return 0;
}

/* -------------------------------------------------------------------------- */
int astral_rand(int gate, int min, int max) {
	unsigned int fortune;

	read(gate, &fortune, 1);
	srandom(fortune);

	return min + (int)(max * (random() / (RAND_MAX + 1.0)));
}
/* -------------------------------------------------------------------------- */
char astral_listen_letter(struct portal *p) {
	char letter_divine;

	do
		if (read(p->gate, &letter_divine, 1) == -1) {
			fprintf(stderr, "astral_listen_letter() failed\n");
			exit(1);
		}
	while
		(letter_divine < 97 || letter_divine > 122);

	return letter_divine;
}
/* -------------------------------------------------------------------------- */
int astral_listen_word(struct portal *p, char* word_divine) {
	int l, w_len;
	char letter;

	/* word-divine length in letters */
	w_len = astral_rand(p->gate, p->l_min, p->l_max);
	memset(word_divine, 0, LETTERS_MAX);

	for (l = 0; l < w_len; l++) {
		letter = astral_listen_letter(p);
		switch (p->w_style) {
			case WORD_STYLE_SIMPLE:
				break;
			case WORD_STYLE_NAME:
				letter = toupper(letter);
				p->w_style = WORD_STYLE_SIMPLE; 
				break;
			case WORD_STYLE_TITLE:
				letter = toupper(letter);
		}
		strncat(word_divine, &letter, 1);
	}

	return w_len;
}
/* -------------------------------------------------------------------------- */
int astral_listen_sentance(struct portal *p, char* sentance_divine) {
	int l, s_len, w_len;
	char word_divine[WORD_MAX_LENGTH];

	/* sentance-divine length in words */
	s_len = astral_rand(p->gate, p->w_min, p->w_max);
	memset(sentance_divine, 0, SENTANCE_MAX_LENGTH);

	switch (p->s_style) {
		case SENTANCE_STYLE_SIMPLE:
			p->w_style = WORD_STYLE_NAME;
			w_len = astral_listen_word(p, word_divine);
			strncat(sentance_divine, word_divine, w_len);
			p->w_style = WORD_STYLE_SIMPLE;
			break;
		case SENTANCE_STYLE_TITLE:
			p->w_style = WORD_STYLE_TITLE;
			w_len = astral_listen_word(p, word_divine);
			break;
	}

	/* The rest of the sentance */
	for (l = 1; l < s_len; l++) {
		w_len = astral_listen_word(p, word_divine);
		strncat(sentance_divine, word_divine, w_len);
		if (l + 1 == s_len)
			strncat(sentance_divine, ".", 1);
		else
			strncat(sentance_divine, " ", 1);			
	}
	
	return strlen(sentance_divine);
}

/* -------------------------------------------------------------------------- */
int astral_listen_paragraph(struct portal *p, char* paragraph_divine) {
	int l, p_len, s_len;
	char sentance_divine[SENTANCE_MAX_LENGTH];

	/* paragraph-divine length in sentances */
	p_len = astral_rand(p->gate, p->s_min, p->s_max);
	memset(paragraph_divine, 0, PARAGRAPH_MAX_LENGTH);

	for (l = 0; l < p_len; l++) {
		s_len = astral_listen_sentance(p, sentance_divine);
		strncat(paragraph_divine, sentance_divine, s_len);
		if (l + 1 < p_len)
			strncat(paragraph_divine, " ", 1);
	}
	return strlen(paragraph_divine);
}

/* -------------------------------------------------------------------------- */
const char *strins(char *dst, char *ins, int pos) {
	char *save;

	if (pos < strlen(dst)) {
		save = (char *)malloc(strlen(dst) + 1);

		strcpy(save, dst + pos);
		strcpy(dst + pos, ins);
		strcat(dst, save);

		free(save);
	} else
		strcat(dst, ins); 

	return dst;
}
/* -------------------------------------------------------------------------- */
int astral_listen(struct portal *p, char *voice_divine) {
	int l, i, v_len, p_len;
	char paragraph[PARAGRAPH_MAX_LENGTH];
	char paragraph_divine[PARAGRAPH_MAX_LENGTH];

	/* voice-divine length in sentances */
	v_len = astral_rand(p->gate, p->p_min, p->p_max);
	memset(voice_divine, 0, STATEMENT_MAX_LENGTH);

	for (l = 0; l < v_len; l++) {
		p_len = astral_listen_paragraph(p, paragraph);
		switch (p->v_style) {
			case VOICE_STYLE_SIMPLE:
				sprintf(paragraph_divine, "%s\n\n", paragraph); 
				break;
			case VOICE_STYLE_BIBLE:
				for (i = p->st_bible_lnlen - 2;
					i < p_len;
					i += p->st_bible_lnlen, p_len += 2
				) 
					strins(paragraph, "\n\t", i);

				sprintf(paragraph_divine, "%d.\t%s\n\n", l + 1, paragraph);
		}

		strncat(voice_divine, paragraph_divine, strlen(paragraph_divine));
	}
	return 0;
}

