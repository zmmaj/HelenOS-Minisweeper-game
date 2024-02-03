/*
 * Copyright (c) 2024 Zmaj from ZmajSoft
 * 
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted .
 * 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 

/** @addtogroup mines
 * @{
 */
/** @file
 */


#include <types/common.h>
#include <io/console.h>
#include <async.h>
#include <stdbool.h>

typedef struct {
	sysarg_t ws_row;
	sysarg_t ws_col;
} winsize_t;

extern console_ctrl_t *console;
extern winsize_t winsize;

extern void moveto(sysarg_t r, sysarg_t c);
extern void clear_screen(void);
extern void scr_clear(void);
extern void scr_end(void);
extern void scr_init(void);
extern void scr_msg(char *, bool);


/** @}
 */
