/*
   +----------------------------------------------------------------------+
   | PHP Version 5                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2008 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Jim Winstead <jimw@php.net>                                  |
   +----------------------------------------------------------------------+
*/

/* $Id: base64.h 279540 2009-04-29 08:57:22Z splanquart $ */

#ifndef BASE64_H
#define BASE64_H

//PHP_FUNCTION(base64_decode);
//PHP_FUNCTION(base64_encode);

//PHPAPI extern 
unsigned char *base64_encode(const char *, size_t, int *);
//PHPAPI extern 
unsigned char *base64_decode_ex(const char *, size_t, int *, int);
//PHPAPI extern 
unsigned char *base64_decode(const char *, size_t, int *);

#endif /* BASE64_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 */
