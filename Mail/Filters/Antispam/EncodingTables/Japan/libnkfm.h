#ifndef _LIBNKFM_H_
#define _LIBNKFM_H_

/*
 *  libnkfm - Kanji conversion library using nkf
 *
 *  Copyright (C), KUBO Takehiro <kubo-t@cx.airnet.ne.jp>
 */

/* nkf_init - libnkfm �̏�����
 *
 * ����:
 *    option    : nkf �̃I�v�V�����Ɠ���
 * �ߒl:
 *    �Ȃ�
 * ���l:
 *    nkf_convert(), nkf_n_convert(), nkf_convert_new() ���ĂԑO�ɕK��
 *    �ĂԂ��ƁB
 */
void nkf_init(const char *option);

/* nkf_convert - �����R�[�h�̕ϊ�(�ϊ���o�b�t�@�̒��������Ȃ�)
 *
 * ����:
 *    outbuf    : �ϊ���̕�����B
 *    inbuf     : �ϊ����̕�����ANUL�I�[�܂ł��ϊ��Ώ�
 * �ߒl:
 *    outbuf �̐擪�A�h���X
 * ���l:
 *    outbuf �̃o�b�t�@���ӂ�̌��m�͂��Ȃ��̂ŁA�\���ȑ傫���̃o�b�t�@
 *    ��p�ӂ��邱�ƁB
 */
char *nkf_convert(char *outbuf, const char *inbuf);

/* nkf_n_convert - �����R�[�h�̕ϊ�(�ϊ���o�b�t�@�̒����w��)
 *
 * ����:
 *    outbuf    : �ϊ���̕�����B
 *    outbuflen : outbuf �̒���
 *    inbuf     : �ϊ����̕�����ANUL�I�[�܂ł��ϊ��Ώ�
 * �ߒl:
 *    outbuf �ɑS���������Ƃ��́Aoutbuf �̐擪�A�h���X
 *    outbuf �ɓ��肫��Ȃ��Ƃ��́ANULL
 */
char *nkf_n_convert(char *outbuf, size_t outbuflen, const char *inbuf);

/* nkf_convert_new - �����R�[�h�̕ϊ�(�ϊ���o�b�t�@�̓��I�m��)
 *
 * ����:
 *    inbuf     : �ϊ����̕�����ANUL�I�[�܂ł��ϊ��Ώ�
 * �ߒl:
 *    �ϊ���̕�����̐擪�A�h���X�B
 *    �������[�m�ۂɎ��s�����Ƃ��� NULL�B
 * ���l:
 *    �ߒl�̕�������ė��p���Ȃ��Ƃ��́A�������[���[�N���ӂ�������
 *    �K�� frre() ���邱�ƁB
 */
char *nkf_convert_new(const char *inbuf);

#endif//_LIBNKFM_H_