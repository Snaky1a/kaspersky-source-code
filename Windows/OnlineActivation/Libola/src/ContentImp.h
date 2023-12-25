/* Generated by Together */

#ifndef _AG_CONTENTIMP_H_
#define _AG_CONTENTIMP_H_

#include <boost/shared_ptr.hpp>
#include "../include/Content.h"

namespace OnlineActivation
{
class HttpResponse;

class ContentImp : public Content
{
public:
	ContentImp(const boost::shared_ptr<HttpResponse>& pResponse);

	virtual ContentType GetType() const;

	virtual const void* GetData() const;

	virtual size_t GetDataSize() const;

private:
	boost::shared_ptr<HttpResponse> m_pResponse;
};

}
#endif //_AG_CONTENTIMP_H_
