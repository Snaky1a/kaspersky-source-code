/* Generated by Together */

#ifndef CONTENT_H
#define CONTENT_H

namespace OnlineActivation
{

/** @interface */
class __declspec(novtable) Content
{
public:
	/**
	 * Content type.
	 */
	enum ContentType
	{
		/**
		 * Other (unknown) content type.
		 */
		CONTENT_OTHER,

		/**
		 * Content type text/html.
		 */
		CONTENT_HTML,

		/**
		 * Content type application/octet-stream.
		 */
		CONTENT_BINARY
	};

	virtual ContentType GetType() const = 0;

	virtual const void* GetData() const = 0;

	virtual size_t GetDataSize() const = 0;
};

}
#endif //CONTENT_H
