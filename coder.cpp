//---------------------------------------------------------------------------


#pragma hdrstop
#include <vcl.h>
#include "coder.h"
#include "Unit1.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


unsigned char outlength =0;
//---------------------------------------------------------------------------
__fastcall TWcoder::TWcoder(unsigned char baselen,unsigned char extlen)
{

        this->g_baselen =   baselen;
        this->g_extlen  =   extlen;
        outlength =  extlen;


}
//---------------------------------------------------------------------------
__fastcall TWcoder::~TWcoder()
{
        this->g_baselen =   0;
        this->g_extlen  =   0;


}
//---------------------------------------------------------------------------
unsigned int __fastcall TWcoder::coder(unsigned char *in_buf,unsigned int len,unsigned char* out_buf,unsigned char channel)
{

          //check in_len
          unsigned int inlen = this->g_baselen ;
          //ͨѶ��·����
          unsigned char channelcnt = 0;

          unsigned short l_crc = 0;
          unsigned int crctag ;

          if(len != this->g_baselen)
          {
                  inlen =  len  ;

          }
          //����������ݵ�����
          for(unsigned int i =0 ;i<inlen ; i++)
          {
               out_buf[i]= in_buf[inlen-i];
               channelcnt += out_buf[i];
               l_crc =  mycrc(out_buf[i],l_crc);

          }



          randomize();
          //������ɲ�λ����
          for(unsigned int i=0;i< (this->g_extlen - inlen - 3) ;i++ )
          {
              //   

               out_buf[inlen + i ] = rand()/255;

                 channelcnt += out_buf[inlen + i ];
                 l_crc =  mycrc(out_buf[inlen + i],l_crc);


          }



          out_buf[this->g_extlen  - 3 ] =  channelcnt+  channel ;


          l_crc =  mycrc(out_buf[this->g_extlen  - 3 ],l_crc);


        //ȷ�������Ƿ���ȷ
          out_buf[this->g_extlen - 3 + 1  ]  =  l_crc/256 ;
          out_buf[this->g_extlen - 3 + 1 + 1 ]  =  l_crc%256 ;


        //������ճ���
        return this->g_extlen;


}

//---------------------------------------------------------------------------
int __fastcall TWcoder::decoder(unsigned char *pbuf ,unsigned char *in_buf,unsigned int len)
{
         unsigned char out_chanel = 0 ;
         unsigned short out_crc  =0;
         unsigned int i =0;
         //�����������
         for(i =0 ;i< len ;i++  )
         {
                if(pbuf[i] != in_buf[len-i])
                {
                      return -1 ;     //�Ǳ����������Կ
                }
                out_chanel += pbuf[i];
                out_crc =  mycrc(pbuf[i],out_crc);
         }
         for(i= len ;i< outlength ; i++  )
         {
               if(i < outlength-3)
               {
                   out_chanel += pbuf[i];
               }
               out_crc =  mycrc(pbuf[i],out_crc);
         }

         if(out_crc == 0 )
         {
                return (unsigned char )(pbuf[outlength-3]-(out_chanel ));
         }
         else
         {
                return -2 ;     //��������������ܲ���ȷ
         }


}

//---------------------------------------------------------------------------
unsigned short mycrc(unsigned char buf,unsigned short crc)
{

        unsigned int i;
        for(i=0x80; i!=0; i>>=1)
        {
                if((crc&0x8000)!=0)
                {
                        crc<<=1;
                        crc^=0x1021;
                }
                else
                {
                        crc<<=1;
                }
                //���ַ�������������
                if((buf&i)!=0)
                {
                        crc^=0x1021;
                }
        }
        return crc;
}


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
