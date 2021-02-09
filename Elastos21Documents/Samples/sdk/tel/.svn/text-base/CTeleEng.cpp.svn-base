#include <elastos.h>
#include <stdio.h>
#include <eztypes.h>
#include <telephonydef.h>
#include <telephony.h>

int main()
{
    printf("............\n");
    IHwMgr    * m_pIHwMgr;
    ECode ec;
    ec = EzCreateObject(CLSID_CTelephony, CTX_SAME_DOMAIN,
                        (RIID)IID_IHwMgr, (IInterface **)&m_pIHwMgr);
    if (FAILED(ec))
        return 1;

    printf("Enter Initialize()\n");
    ec = m_pIHwMgr->Initialize();
    if (FAILED(ec))
        return 1;
    printf("Initialize\n");

    ec = m_pIHwMgr->SetEquipmentState(TAPI_EQUIPSTATE_NOTXRX);
    if (FAILED(ec))
        return 1;
    printf("Close TXRX\n");

    return 0;
}
