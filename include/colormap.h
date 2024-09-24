#pragma once

#include <qcolor.h>
#include <qlist.h>

namespace Colormap
{

	class ColormapBase
	{

	protected:
		ColormapBase();
		~ColormapBase();

	public:
		virtual int length() const;
		virtual QColor color(double t);
		const QList<QColor>& colormap();
		
	protected:
		QList<QColor> m_colormap;

	};

	class Jet : public ColormapBase
	{
	public:
		Jet();
		~Jet();
	};
};




