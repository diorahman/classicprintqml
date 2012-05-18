#ifndef CLASSICPRINTQML_CLASSICPRINTDECLARATIVE_H
#define CLASSICPRINTQML_CLASSICPRINTDECLARATIVE_H

#include <QtCore>
#include <QtGui>
#include <QtDeclarative>

#include "ClassicPrint.h"
#include "ClassicPrintLens.h"
#include "ClassicPrintFilm.h"
#include "ClassicPrintProcessing.h"

class ClassicPrintDeclarative : public QObject {
    Q_OBJECT

    public:
        ClassicPrintDeclarative(QObject *parent=NULL)
            : QObject(parent),
              m_sequence(0),
              m_timer()
        {
            m_timer.setInterval(500);
            m_timer.setSingleShot(true);

            QObject::connect(&m_timer, SIGNAL(timeout()),
                    this, SIGNAL(sequenceChanged()));

            /* Lens */
            QObject::connect(this, SIGNAL(radiusChanged()),
                    this, SLOT(contentUpdated()));

            QObject::connect(this, SIGNAL(darknessChanged()),
                    this, SLOT(contentUpdated()));

            QObject::connect(this, SIGNAL(dodgeChanged()),
                    this, SLOT(contentUpdated()));

            QObject::connect(this, SIGNAL(defocusChanged()),
                    this, SLOT(contentUpdated()));

            /* Film */
            QObject::connect(this, SIGNAL(temperatureChanged()),
                    this, SLOT(contentUpdated()));

            QObject::connect(this, SIGNAL(noiseChanged()),
                    this, SLOT(contentUpdated()));

            /* Processing */
            QObject::connect(this, SIGNAL(contrastChanged()),
                    this, SLOT(contentUpdated()));

            QObject::connect(this, SIGNAL(colourisationChanged()),
                    this, SLOT(contentUpdated()));

            QObject::connect(this, SIGNAL(frameSizeChanged()),
                    this, SLOT(contentUpdated()));

            QObject::connect(this, SIGNAL(lightLeakChanged()),
                    this, SLOT(contentUpdated()));
        }

        static void init() {
            classicPrint = new ClassicPrint;
            classicPrint->load(":/classicPrintData/settings.xml");
            qmlRegisterType<ClassicPrintDeclarative>("org.maemo.classicprint",
                    1, 0, "ClassicPrint");
        }

        static ClassicPrint *getClassicPrint() {
            return classicPrint;
        }



        /* Lens */

        qreal radius() {
            return getClassicPrint()->getCurrentLens()->radius()/99.;
        }

        void setRadius(qreal radius) {
            getClassicPrint()->getCurrentLens()->setRadius(radius*99.);
            emit radiusChanged();
        }

        Q_PROPERTY(qreal radius
                READ radius
                WRITE setRadius
                NOTIFY radiusChanged)

        qreal darkness() {
            return getClassicPrint()->getCurrentLens()->darkness()/100.;
        }

        void setDarkness(qreal darkness) {
            getClassicPrint()->getCurrentLens()->setDarkness(darkness*100.);
            emit darknessChanged();
        }

        Q_PROPERTY(qreal darkness
                READ darkness
                WRITE setDarkness
                NOTIFY darknessChanged)

        qreal dodge() {
            return getClassicPrint()->getCurrentLens()->dodge()/100.;
        }

        void setDodge(qreal dodge) {
            getClassicPrint()->getCurrentLens()->setDodge(dodge*100.);
            emit dodgeChanged();
        }

        Q_PROPERTY(qreal dodge
                READ dodge
                WRITE setDodge
                NOTIFY dodgeChanged)

        bool defocus() {
            return getClassicPrint()->getCurrentLens()->defocus();
        }

        void setDefocus(bool defocus) {
            if (defocus != this->defocus()) {
                getClassicPrint()->getCurrentLens()->setDefocus(defocus);
                emit defocusChanged();
            }
        }

        Q_PROPERTY(bool defocus
                READ defocus
                WRITE setDefocus
                NOTIFY defocusChanged)


        /* Film */
        qreal temperature() {
            return getClassicPrint()->getCurrentFilm()->temperature()/100.;
        }

        void setTemperature(qreal temperature) {
            getClassicPrint()->getCurrentFilm()->setTemperature(temperature*100.);
            emit temperatureChanged();
        }

        Q_PROPERTY(qreal temperature
                READ temperature
                WRITE setTemperature
                NOTIFY temperatureChanged)

        qreal noise() {
            return getClassicPrint()->getCurrentFilm()->noise()/100.;
        }

        void setNoise(qreal noise) {
            getClassicPrint()->getCurrentFilm()->setNoise(noise*100.);
            emit noiseChanged();
        }

        Q_PROPERTY(qreal noise
                READ noise
                WRITE setNoise
                NOTIFY noiseChanged)


        /* Processing */

        qreal contrast() {
            return getClassicPrint()->getCurrentProcessing()->contrast()/100.;
        }

        void setContrast(qreal contrast) {
            getClassicPrint()->getCurrentProcessing()->setContrast(contrast*100.);
            emit contrastChanged();
        }

        Q_PROPERTY(qreal contrast
                READ contrast
                WRITE setContrast
                NOTIFY contrastChanged)

        qreal colourisation() {
            return getClassicPrint()->getCurrentProcessing()->colourisationPercent()/100.;
        }

        void setColourisation(qreal colourisation) {
            getClassicPrint()->getCurrentProcessing()->setColourisationPercent(colourisation*100.);
            emit colourisationChanged();
        }

        Q_PROPERTY(qreal colourisation
                READ colourisation
                WRITE setColourisation
                NOTIFY colourisationChanged)

        qreal frameSize() {
            return getClassicPrint()->getCurrentProcessing()->frameSizePercent()/15.;
        }

        void setFrameSize(qreal frameSize) {
            getClassicPrint()->getCurrentProcessing()->setFrameSizePercent(frameSize*15.);
            emit frameSizeChanged();
        }

        Q_PROPERTY(qreal frameSize
                READ frameSize
                WRITE setFrameSize
                NOTIFY frameSizeChanged)

        int lightLeak() {
            QString value = getClassicPrint()->getCurrentProcessing()->lightLeak();
            if (value == "Light Leak 1.jpg") {
                return 1;
            } else if (value == "Light Leak 3.jpg") {
                return 2;
            } else if (value == "Random") {
                return -1;
            } else {
                return 0;
            }
        }

        void setLightLeak(int lightLeak) {
            if (this->lightLeak() != lightLeak) {
                QString value;
                switch (lightLeak) {
                    case 1:
                        value = "Light Leak 1.jpg";
                        break;
                    case 2:
                        value = "Light Leak 3.jpg";
                        break;
                    case -1:
                        value = "Random";
                        break;
                    default:
                        value = "";
                        break;
                }

                getClassicPrint()->getCurrentProcessing()->setLightLeak(value);
                emit lightLeakChanged();
            }
        }

        Q_PROPERTY(int lightLeak
                READ lightLeak
                WRITE setLightLeak
                NOTIFY lightLeakChanged)


        int sequence() { return m_sequence; }
        Q_PROPERTY(int sequence READ sequence NOTIFY sequenceChanged)

    signals:
        /* Lens */
        void radiusChanged();
        void darknessChanged();
        void dodgeChanged();
        void defocusChanged();

        /* Film */
        void temperatureChanged();
        void noiseChanged();

        /* Processing */
        void contrastChanged();
        void colourisationChanged();
        void frameSizeChanged();
        void lightLeakChanged();

        void sequenceChanged();

    public slots:
        void contentUpdated() {
            m_sequence++;
            // wait a bit to avoid too many updates
            m_timer.start();
        }

    private:
        static ClassicPrint *classicPrint;

        int m_sequence;
        QTimer m_timer;
};

#endif
