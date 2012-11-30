#ifndef B9PRINT_H
#define B9PRINT_H

#include <QDialog>
#include <QDateTime>
#include <QHideEvent>
#include <QSettings>
#include "helpsystem.h"
#include "b9terminal.h"

namespace Ui {
class B9Print;
}

class B9Print : public QDialog
{
    Q_OBJECT
    
public:
    explicit B9Print(B9Terminal *pTerm, QWidget *parent = 0);
    ~B9Print();
    // If PrintPreview we do not power up the projector.  If UsePrimaryMonitor we force the output to the primary monitor
    void print3D(CrushedPrintJob *pCPJ, int iXOff, int iYOff, int iTbase, int iTover, int iTattach, int iNumAttach = 1, int iLastLayer = 0, bool bPrintPreview = false, bool bUsePrimaryMonitor = false);
    
signals:
    void eventHiding();

public slots:
    void setProjMessage(QString sText);
    QString updateTimes();

private slots:
    void showHelp();
    void on_updateConnectionStatus(QString sText);
    void on_updateProjectorOutput(QString sText);
    void on_updateProjectorStatus(QString sText);
    void on_updateProjector(B9PrinterStatus::ProjectorStatus eStatus);
    void on_signalAbortPrint();

    void exposeTBaseLayer();
    void startExposeTOverLayers();
    void exposureOfCurTintLayerFinished();
    void exposureOfTOverLayersFinished();

    void on_pushButtonPauseResume_clicked();

    void on_pushButtonAbort_clicked(QString sAbortText="User Directed Abort.");

private:
    enum {PRINT_NO, PRINT_SETUP1, PRINT_SETUP2, PRINT_RELEASING, PRINT_EXPOSING, PRINT_ABORT, PRINT_DONE};
    enum {PAUSE_NO, PAUSE_WAIT, PAUSE_YES};

    void keyPressEvent(QKeyEvent * pEvent);		// Handle key press events
    void hideEvent(QHideEvent *event);
    void closeEvent ( QCloseEvent * event );

    double curLayerIndexMM();
    void setSlice(int iSlice);

    HelpSystem m_HelpSystem;
    Ui::B9Print *ui;

    B9Terminal* m_pTerminal;
    CrushedPrintJob* m_pCPJ;
    int m_iTbase,  m_iTover, m_iTattach, m_iNumAttach;
    int m_iXOff, m_iYOff;
    int m_iPrintState;
    int m_iCurLayerNumber;
    int m_iLastLayer;
    double m_dLayerThickness;
    int m_iPaused;
    bool m_bAbort;
    QString m_sAbortMessage;
    double m_dTintMS;
    int m_iTintNum, m_iCurTintIndex, m_iMinimumTintMS,m_iMinimumTintMSWorstCase;
    QTime m_vClock;
    QSettings m_vSettings;

};

#endif // B9PRINT_H
