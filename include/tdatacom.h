#ifndef __DATACOM_H__
#define __DATACOM_H__

#define DataOK   0
#define DataErr -1

// TDataCom ÿâëÿåòñÿ îáùèì áàçîâûì êëàññîì
class TDataCom
{
protected:
    int RetCode; // Êîä çàâåðøåíèÿ
    int SetRetCode(int ret) { return RetCode = ret; }
public:
    TDataCom() : RetCode(DataOK) {}
    virtual ~TDataCom() {}
    int GetRetCode()
    {
        int temp = RetCode;
        RetCode = DataOK;
        return temp;
    }
};

#endif

