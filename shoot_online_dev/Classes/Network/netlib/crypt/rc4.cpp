/*
 * rc4.c
 *
 * Copyright (c) 1996-2000 Whistle Communications, Inc.
 * All rights reserved.
 * 
 * Subject to the following obligations and disclaimer of warranty, use and
 * redistribution of this software, in source or object code forms, with or
 * without modifications are expressly permitted by Whistle Communications;
 * provided, however, that:
 * 1. Any and all reproductions of the source or object code must include the
 *    copyright notice above and the following disclaimer of warranties; and
 * 2. No rights are granted, in any manner or form, to use Whistle
 *    Communications, Inc. trademarks, including the mark "WHISTLE
 *    COMMUNICATIONS" on advertising, endorsements, or otherwise except as
 *    such appears in the above copyright notice or in the software.
 * 
 * THIS SOFTWARE IS BEING PROVIDED BY WHISTLE COMMUNICATIONS "AS IS", AND
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, WHISTLE COMMUNICATIONS MAKES NO
 * REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED, REGARDING THIS SOFTWARE,
 * INCLUDING WITHOUT LIMITATION, ANY AND ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
 * WHISTLE COMMUNICATIONS DOES NOT WARRANT, GUARANTEE, OR MAKE ANY
 * REPRESENTATIONS REGARDING THE USE OF, OR THE RESULTS OF THE USE OF THIS
 * SOFTWARE IN TERMS OF ITS CORRECTNESS, ACCURACY, RELIABILITY OR OTHERWISE.
 * IN NO EVENT SHALL WHISTLE COMMUNICATIONS BE LIABLE FOR ANY DAMAGES
 * RESULTING FROM OR ARISING OUT OF ANY USE OF THIS SOFTWARE, INCLUDING
 * WITHOUT LIMITATION, ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * PUNITIVE, OR CONSEQUENTIAL DAMAGES, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES, LOSS OF USE, DATA OR PROFITS, HOWEVER CAUSED AND UNDER ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF WHISTLE COMMUNICATIONS IS ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * $FreeBSD: src/sys/crypto/rc4/rc4.c,v 1.2.2.1 2000/04/18 04:48:31 archie Exp $
 */

#include "rc4.h"

namespace scnet
{

static void swap_bytes(uint8_t *a, uint8_t *b)
{
	uint8_t temp;
    
	temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * Initialize an RC4 state buffer using the supplied key,
 * which can have arbitrary length.
 */
void
RC4::init(const uint8_t *key, int keylen)
{
	uint8_t j;
	int i;
    
	/* Initialize state with identity permutation */
	for (i = 0; i < 256; i++)
		_state.perm[i] = (uint8_t)i; 
	_state.index1 = 0;
	_state.index2 = 0;
    
	/* Randomize the permutation using key data */
	for (j = i = 0; i < 256; i++) {
		j += _state.perm[i] + key[i % keylen]; 
		swap_bytes(&_state.perm[i], &_state.perm[j]);
	}
}

RC4::RC4(const uint8_t *key, int keylen)
{
    init(key, keylen);
}

RC4::RC4(const std::string &key)
{
    init((const uint8_t *)key.data(), key.length());
}

/*
 * Encrypt some data using the supplied RC4 state buffer.
 * The input and output buffers may be the same buffer.
 * Since RC4 is a stream cypher, this function is used
 * for both encryption and decryption.
 */
void
RC4::crypt(const uint8_t *inbuf, uint8_t *outbuf, int buflen)
{
	int i;
	uint8_t j;
    
	for (i = 0; i < buflen; i++) {
        
		/* Update modification indicies */
		_state.index1++;
		_state.index2 += _state.perm[_state.index1];
        
		/* Modify permutation */
		swap_bytes(&_state.perm[_state.index1],
                   &_state.perm[_state.index2]);
        
		/* Encrypt/decrypt next byte */
		j = _state.perm[_state.index1] + _state.perm[_state.index2];
		outbuf[i] = inbuf[i] ^ _state.perm[j];
	}
}

void
RC4::crypt(const std::string &inbuf, std::string &outbuf)
{
    size_t len = inbuf.size();
    uint8_t* out = new uint8_t[len];
    crypt((const uint8_t *)inbuf.data(), out, len);
    outbuf.assign((char *)out, len);
	delete[] out;
}

}
