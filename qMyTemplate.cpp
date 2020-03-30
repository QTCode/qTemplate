#include "qMyTemplate.h"

class qMyTemplatePrivate
{
	Q_DECLARE_PUBLIC(qMyTemplate);
protected:
	qMyTemplate* const q_ptr;

public:
	qMyTemplatePrivate(qMyTemplate* object);
	~qMyTemplatePrivate();
};

qMyTemplatePrivate::qMyTemplatePrivate(qMyTemplate* object)
	:q_ptr(object)
{

}

qMyTemplatePrivate::~qMyTemplatePrivate()
{

}

qMyTemplate::qMyTemplate(QObject* parent)
	:QObject(parent), d_ptr(new qMyTemplatePrivate(this))
{
	Q_D(qMyTemplate);

}

qMyTemplate::~qMyTemplate()
{
	Q_D(qMyTemplate);

}
