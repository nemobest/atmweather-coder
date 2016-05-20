//---------------------------------------------------------------------------

#ifndef coderH
#define coderH

#define A_KEY 16
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

unsigned short mycrc(unsigned char buf,unsigned short crc);

class TWcoder
{

private:	// User declarations
        unsigned int g_baselen;    //����Դ�ĳ���
        unsigned int g_extlen;     //������ݵĳ���



public:		// User declarations
        __fastcall TWcoder(unsigned char baselen,unsigned char extlen);
        __fastcall ~TWcoder();

        unsigned int __fastcall coder(unsigned char *in_buf,unsigned int len,unsigned char* out_buf,unsigned char channel);
        int __fastcall TWcoder::decoder(unsigned char *pbuf ,unsigned char *in_buf,unsigned int len) ;



};





#endif
