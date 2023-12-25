/*******************************************************************************
 * Project: Content Filtration Library                                         *
 * (C) 2001-2003, Ashmanov & Partners company, Moscow, Russia                  *
 * Contact: info@ashmanov.com, http://www.ashmanov.com                         *
 * --------------------------------------------------------------------------- *
 * File: message.h                                                             *
 * Created: Tue Nov 20 23:52:36 2001                                           *
 * Desc: Message abstraction                                                   *
 *******************************************************************************/

/**
 * \file  message.h
 * \brief Message abstraction
 */

#ifndef __message_h__
#define __message_h__
#include <stdlib.h>
#include <stdio.h>

#ifdef WIN32
#pragma pack(push, 8)
#else
#pragma pack(8)
#endif

#ifdef __cplusplus
extern "C"
{
#endif
  
    /**
     * \brief Text field of message.
     */
    typedef struct __msg_text_field
    {
	const char*   ptr;           /*!< Doesn't supposed to be zero-terminated */
	unsigned long count;
	unsigned long alloc;         /*!< Must be zero, if ptr is not allocated in CFLib functions */
    } msg_text_field;
    
    /**
     * \brief Reserved structure
     */
    typedef struct __msg_reserved
    {
	unsigned long r1;
	unsigned long r2;
    } msg_reserved;

#define MSG_ATTACHMENT_ALLOCATED    0x00000001U
#define MSG_FILENAME_ALLOCATED      0x00000002U
#define MSG_DISPOSITION_ATTACHMENT  0x00000004U
#define MSG_ALTERNATIVE             0x00000008U
#define MSG_ATTACHMENT_EXTRACTED    0x00000010U
#define MSG_CONTENTTYPE_ALLOCATED   0x00000020U
#define MSG_PARSE_ANYWAY            0x00000040U
    
    /**
     * \brief Message attachment
     */
    typedef struct __msg_attachment
    {
	unsigned long flags;         /*!< For internal use only */
	
	const unsigned char* ptr;    /*!< binary data, may contain zeros */
	unsigned long  count;        /*!< length in bytes */
	unsigned long  alloc; 
	
	msg_text_field content_type; /*!< content type of attachment, can be NULL */
	msg_text_field filename;     /*!< filename of attachment from content-dispsition header */
	
	msg_reserved reserved;       /*!< Parsed text ??? */
	
    } msg_attachment;
    
    /**
     * \brief Message URLs 
     */
    typedef struct __message_url
    {
	const char *url;
	size_t length;
    } message_url;

    typedef struct __message_urls
    {
	message_url *urls;
	size_t used;
	size_t alloc;
    } message_urls;
    
    /**
     * \brief Message abstraction.
     */

#define MESSAGE_FLAG_CRYPTED 0x00000001U

    struct __message
    {
	msg_text_field origin; /*!< source of this message, filled in msg_create_mime. */

	msg_text_field body;   
	msg_text_field subject;

	msg_attachment* attachments; /*!< Array of attachment and inline parts of message. 
				      * If body have content-type, differenet from text/plain,
				      * it must be placed in this array too.
				      */
	unsigned long   attachments_count; /*!< Size of attachments array */
	unsigned long   current_attachment; /*!< Uses only during attachments parsing */

        unsigned int    flags;        /*!< MESSAGE_FLAG_* combination */

        msg_text_field  headers; /*!< Set by external utility  */
        
	message_urls	urls;	/*!< URLs from all attachments and message body */

    };
    
    typedef struct __message message;
    
    /**
     * \brief Message structure constructor from MIME memory pool
     * 
     * \param msg --- resulting message,
     * \param msg_text --- MIME string,
     * \param msg_length --- MIME string length, can be 0 (means: till end of message or zero)
     *
     * \return zero on success or some errno
     */
    int  message_create_mime(message* msg, const char* msg_text, unsigned long msg_length);

#define MIME_EXTRACT_HTML       0x00000001U
#define MIME_EXTRACT_MICROSOFT  0x00000002U
#define MIME_EXTRACT_RTF        0x00000004U
#define MIME_EXTRACT_URLS       0x00000008U

#define MIME_EXTRACT_DEFAULTS (MIME_EXTRACT_HTML | MIME_EXTRACT_MICROSOFT | MIME_EXTRACT_RTF | MIME_EXTRACT_URLS)

    struct mime_config {

        unsigned int extractor_flags;

    };

    int  message_create_mime_ex(message* msg, const char* msg_text, unsigned long msg_length, 
                                struct mime_config *mc);


    /**
     * \brief Add attachment to message.
     *
     * \param msg --- message, to work with,
     * \param att --- attachment to add.
     *
     * \return nonzero at error, 0 otherwise.
     *
     * All data external for attachment (ptr, content_type and filename)  must be deleted 
     * by user-side after processing the message, attachment struct itself copied into 
     * attachments array and may be freed after call of message_add_attachment.
     */
    int  message_add_attachment(message* msg, msg_attachment *att);
    
    /**
     * \brief Destroy the message
     *
     * This function must be called, if message have correct filled 
     * attachments (by message_create_mime() or message_add_attachment());
     */
    void message_destroy(message* msg);
    
    void dump_message(message* m, FILE* f);
#ifdef __cplusplus
}
#endif

#ifdef WIN32
#pragma pack(pop)
#else
#pragma pack()
#endif

#endif // __message_h__

/*
 * <eof message.h>
 */
