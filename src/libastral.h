/*
 * ----------------------------------------------------------------------------
 * "THE MODIFIED BEER-WARE LICENSE" (Revision 1):
 * <zmey20000@yahoo.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Mikhail E. Zakharov
 * ----------------------------------------------------------------------------
 */

#ifndef __ASTRAL_LIB_H_
#define __ASTRAL_LIB_H_

/* ASTRAL API top-level functions */
struct portal* astral_open();
int astral_close(struct portal *p);
int astral_listen(struct portal *p, char *voice_divine);
/* int astral_pray(struct portal *p, char* pray); */

/* ASTRAL low-level API */
#define	LETTERS_MIN		1
#define LETTERS_MAX		10
#define WORDS_MIN		1
#define WORDS_MAX		16
#define SENTANCES_MIN		1
#define SENTANCES_MAX 		8
#define PARAGRAPHS_MIN		1
#define PARAGRAPHS_MAX		4

#define WORD_MAX_LENGTH		(LETTERS_MAX + 1)
#define SENTANCE_MAX_LENGTH	(WORDS_MAX * WORD_MAX_LENGTH + 1) /* "Blah-blah-blah. " <--dot-space */
#define PARAGRAPH_MAX_LENGTH	(SENTANCES_MAX * SENTANCE_MAX_LENGTH + 90)
#define STATEMENT_MAX_LENGTH	PARAGRAPHS_MAX * (PARAGRAPH_MAX_LENGTH) /* 99. Foo-bar."\n\n" */

#define WORD_STYLE_SIMPLE	0
#define WORD_STYLE_NAME		1
#define WORD_STYLE_TITLE	2

#define SENTANCE_STYLE_SIMPLE	0	
#define SENTANCE_STYLE_TITLE	1

#define VOICE_STYLE_SIMPLE	0
#define VOICE_STYLE_BIBLE	1
#define VOICE_STYLE_BIBLE_LNLEN	32	

struct portal {
	int gate;

        int l_min;
        int l_max;
        int w_min;
        int w_max;
        int s_min;
        int s_max;
        int p_min;
        int p_max;
        
	int w_style;
	int s_style;
        int v_style;

        int st_bible_lnlen;
};


int astral_rand(int gate, int min, int max);
char astral_listen_letter(struct portal *p);
int astral_listen_word(struct portal *p, char* word_divine);
int astral_listen_sentance(struct portal *p, char* sentance_divine);
int astral_listen_paragraph(struct portal *p, char* paragraph_divine);

#endif /* __ASTRAL_LIB_H_ */

