#include "bsp.h"
#include "bsp.h"

#include "bsp.h"


#define Zero_Degree           5828    

#define COMPENSATION_VALUE    0

#define NTC_RES_F3425         1



uint16_t *pArray[23];

uint8_t length_simple;

uint8_t array_subscript;

uint8_t disp_temp_degree;
uint8_t search_key;
uint8_t compare_up_counter,compare_down_counter;

static int8_t  Binary_Search(const uint8_t *array ,uint8_t key,uint8_t length);

static uint8_t Calculate_Display_Temperature_Value(const uint16_t *pt,uint8_t key,uint16_t ntc_res_value,uint8_t length);


typedef enum{

   degree_zero = 0,
   degree_one = 1,
   degree_two = 2,
   degree_three = 3,
   degree_four = 4,
   degree_five =5,
   degree_six = 6,
   degree_seven = 7,
   degree_eight = 8,
   degree_nine = 9,
   degree_ten = 10,
   degree_eleven = 11,
   degree_twelve = 12,
   degree_thirteen =13,
   degree_fourteen = 14,
   degree_fiveteen =15,
   degree_sixteen =16,
   degree_seventeen =17,
   degree_eighteen = 18,
   degree_nineteen = 19,
   degree_twenty = 20,
   degree_twenty_one = 21,
   degree_twenty_two =22,
   degree_twenty_three =23,
   degree_twenty_four =24
   
   


}degree_state;

typedef struct _ntc_t{

   uint8_t temperature_value;
  
   uint8_t temperature_rectify_value;
   uint16_t ntc_res_read_adc_value;
   
}ntc_res_t;


ntc_res_t ntc_t;


int8_t left_point =0;
int8_t right_point ;

int8_t mid_value;


//NTC RES F3950  new calculation 

static const uint16_t R10K_0_1[2]={2432,2404}; //array[0] = error range = 28
static const uint16_t R10K_2_4[3]={2375,2346,2317}; //array[0] = error range = 32
static const uint16_t R10K_5_7[3]={2287,2257,2226};//array[1] error range = 32
static const uint16_t R10K_8_11[4]={2196,2165,2134,2102}; //array[2] error range = 32
static const uint16_t R10K_12_14[3]={2071,2039,2007}; //array[2] error range = 32
static const uint16_t R10K_15_17[3]={1976,1944,1912}; //array[2] error range = 32


//
static const uint16_t R10K_18_20[3]={1880,1848,1816}; //array[0] = error range = 32
static const uint16_t R10K_21_23[3]={1784,1752,1721};//array[1] error range = 32
static const uint16_t R10K_24_26[3]={1689,1658,1627}; //array[2] error range = 32

static const uint16_t R10K_27_30[4]={1597,1567,1537,1507}; //array[3] =error range = 30
static const uint16_t R10K_31_33[3]={1477,1448,1419};       //array[4] =error range = 29
static const uint16_t R10K_34_37[4]={1391,1362,1334,1307}; //array[5]=error range= 27
static const uint16_t R10K_38_41[4]={1279,1253,1226,1200};  //array[6]=error range = 27
static const uint16_t R10K_42_44[3]={1175,1149,1124};  //array[7]=error range = 25

static const uint16_t R10K_45_49[5]={1099,1075,1051,1028,1005}; //array[8]=error range = 24

static const uint16_t R10K_50_53[4]={982,960,938,917};  //array[9]锟??? error range = 21
static const uint16_t R10K_54_58[5]={896,875,855,835,816}; //array[10]锛歟rror range = 19

static const uint16_t R10K_59_64[6]={797,779,760,743,725,708};  //array[11]锛歟rror range = 16
static const uint16_t R10K_65_71[7]={692,675,660,644,629,614,600};  //array[12]锟??? error range = 14 

static const uint16_t R10K_72_78[7]={585,572,558,545,532,520,507}; //array[13]:error range = 12

static const uint16_t R10K_79_88[10]={495,484,472,461,450,440,430,419,410,400}; ////array[14]:error range = 10

static const uint16_t R10K_89_100[12] ={391,382,373,364,356,348,340,332,324,317,309,302}; //array[15]:error range = 8

static const uint16_t R10K_101_118[18] ={295,289,282,276,270,264,258,252,246,241,235,230,225,220,215,211,206,201}; //array[16]:error range = 4

static const uint16_t R10K_119_120[2]={197,193}; //



///


static const uint8_t R10K_Init_0_120_simple[24]={

    24,23,22,21,20,
	19,18,17,16,15,
	14,13,12,11,10,
	9,8,7,6,5,
	4,3,2,1
};

volatile uint8_t local_ntc_value,read_ntc_temperature_value,local_ntc_rectify_value;


static void Calculate_Speicial_Temperature_Value(uint8_t temp);

uint16_t ptc_res_temp_voltage;

uint8_t disp_value;
uint16_t adcx,temp_vlue;

/*****************************************************************
	*
	*Function Name: static uint16_t Get_Adc(uint32_t ch)  
	*Function ADC input channel be selected "which one channe"
	*Input Ref: which one ? AC_Channel_?
	*Return Ref: No
	*
*****************************************************************/
void Get_Ntc_Resistance_Temperature_Handler(uint16_t voltage)
{
   
   ntc_t.ntc_res_read_adc_value = voltage ;

    temp_vlue= voltage /100;
	
	length_simple =  sizeof(R10K_Init_0_120_simple)/sizeof(R10K_Init_0_120_simple[0]);
    
   	 disp_temp_degree = Binary_Search(R10K_Init_0_120_simple,temp_vlue,length_simple);
    
	Calculate_Speicial_Temperature_Value(disp_temp_degree);
    
    read_ntc_temperature_value = ntc_res_linear_value(local_ntc_value);

}

uint8_t getNtc_linearTemperature_value(void)
{

      return read_ntc_temperature_value ;
}
/*****************************************************************
	*
	*Function Name: void getNtc_temperatureValue_init(uint16_t voltage)
	*Function :
	*Input Ref: NO
	*Return Ref: No
	*
*****************************************************************/
void getNtc_temperatureValue_init(uint16_t voltage)
{
   // static uint8_t read_adc_value;


    ntc_t.ntc_res_read_adc_value = voltage ;

    temp_vlue= voltage /100;
	
	length_simple =  sizeof(R10K_Init_0_120_simple)/sizeof(R10K_Init_0_120_simple[0]);
    
   	 disp_temp_degree = Binary_Search(R10K_Init_0_120_simple,temp_vlue,length_simple);
    
	Calculate_Speicial_Temperature_Value(disp_temp_degree);
    
    read_ntc_temperature_value = local_ntc_value;
     
    

 }

/*************************************************************************
	*
	*Functin Name: static int8_t  Binary_Search(uint8_t *R10K_NTC_81 ,uint8_t key)
	*Funtion: binary search arithmetic
	*
	*
	*
*************************************************************************/
static int8_t  Binary_Search(const uint8_t *array ,uint8_t key,uint8_t length)
{
    left_point =0 ;
	right_point = length -1;
   while(left_point <= right_point){

        mid_value = (left_point + right_point)/2;

        if(key == array[mid_value]){

		    return   mid_value;

		}
        else if(array[mid_value] >   key ){ //move right  -> right small numbers

             left_point = mid_value +1;
			

		}
		else if(array[mid_value] < key){ //move left -> left big numbers

          right_point = mid_value -1;
		   

       }
	} 
   
	return -1;
} 

/******************************************************************************
	*
	*Function Name: static void Calculate_Speicial_Temperature_Value(uint8_t temp)
	*Function :calculate special value
	*Input Ref: speical transmit display temperature value 
	*Return Ref:NO
	*
******************************************************************************/
static void Calculate_Speicial_Temperature_Value(uint8_t temp)
{
  // static uint8_t array_subscript;

   switch(temp){


   case degree_zero: //zero degree 0~1 degree

           // zero_d =2;
          array_subscript =  Calculate_Display_Temperature_Value(R10K_0_1,0,ntc_t.ntc_res_read_adc_value,2);
		 if(array_subscript > 1)array_subscript=1;

         switch(array_subscript){

         case 0:
        		 local_ntc_value = 0 + local_ntc_rectify_value +COMPENSATION_VALUE;

         break;

         case 1:
  		 	local_ntc_value = 1 + local_ntc_rectify_value +COMPENSATION_VALUE;

  		 break;

  		}

     break;


      case degree_one: //zero degree 2~4 degree

		// zero_d =2;
		array_subscript =  Calculate_Display_Temperature_Value(R10K_2_4,1,ntc_t.ntc_res_read_adc_value,3);
		if(array_subscript > 2)array_subscript=2;

		switch(array_subscript){

			case 0:
			 local_ntc_value = 2 + local_ntc_rectify_value +COMPENSATION_VALUE;

			break;

			case 1:
			local_ntc_value = 3 + local_ntc_rectify_value +COMPENSATION_VALUE;

			break;

			case 2:
			local_ntc_value = 4 + local_ntc_rectify_value +COMPENSATION_VALUE;

			break;

		}

     break;

	  case degree_two: //zero degree 5~7 degree

			// zero_d =2;
			array_subscript =  Calculate_Display_Temperature_Value(R10K_5_7,2,ntc_t.ntc_res_read_adc_value,3);
			if(array_subscript > 2)array_subscript=2;

			switch(array_subscript){

				case 0:
				 local_ntc_value = 5 + local_ntc_rectify_value +COMPENSATION_VALUE;

				break;

				case 1:
				local_ntc_value = 6 + local_ntc_rectify_value +COMPENSATION_VALUE;

				break;

				case 2:
				local_ntc_value = 7 + local_ntc_rectify_value +COMPENSATION_VALUE;

				break;

			}

		 break;

		case degree_three: //zero degree 8~11 degree

		// zero_d =2;
		array_subscript =  Calculate_Display_Temperature_Value(R10K_8_11,3,ntc_t.ntc_res_read_adc_value,4);
		if(array_subscript > 3)array_subscript=3;

		switch(array_subscript){

			case 0:
			 local_ntc_value = 8 + local_ntc_rectify_value +COMPENSATION_VALUE;

			break;

			case 1:
			local_ntc_value = 9 + local_ntc_rectify_value +COMPENSATION_VALUE;

			break;

			case 2:
			local_ntc_value = 10 + local_ntc_rectify_value +COMPENSATION_VALUE;

			break;

			case 3:
			 local_ntc_value = 11 + local_ntc_rectify_value +COMPENSATION_VALUE;

			break;

		}

		break;

		case degree_four: //zero degree 12~14 degree

			// zero_d =2;
			array_subscript =  Calculate_Display_Temperature_Value(R10K_12_14,4,ntc_t.ntc_res_read_adc_value,3);
			if(array_subscript > 2)array_subscript=2;
			switch(array_subscript){

				case 0:
				 local_ntc_value = 12 + local_ntc_rectify_value +COMPENSATION_VALUE;

				break;

				case 1:
				local_ntc_value = 13 + local_ntc_rectify_value +COMPENSATION_VALUE;

				break;

				case 2:
				local_ntc_value = 14 + local_ntc_rectify_value +COMPENSATION_VALUE;

				break;

			}

		break;


		case degree_five: //zero degree 15~17 degree

		// zero_d =2;
		array_subscript =  Calculate_Display_Temperature_Value(R10K_15_17,5,ntc_t.ntc_res_read_adc_value,3);
		if(array_subscript > 2)array_subscript=2;

		switch(array_subscript){

			case 0:
			local_ntc_value = 15 + local_ntc_rectify_value +COMPENSATION_VALUE;

			break;

			case 1:
			local_ntc_value = 16 + local_ntc_rectify_value +COMPENSATION_VALUE;

			break;

			case 2:
			local_ntc_value = 17 + local_ntc_rectify_value +COMPENSATION_VALUE;

			break;

		}

		break;


    // older data
    case degree_six: //zero degree 18 `` 20 degree

         // zero_d =2;
        array_subscript =  Calculate_Display_Temperature_Value(R10K_18_20,6,ntc_t.ntc_res_read_adc_value,3);
        if(array_subscript > 2)array_subscript=2;
       switch(array_subscript){

       case 0:
      		 local_ntc_value = 18 + local_ntc_rectify_value +COMPENSATION_VALUE;

       break;

       case 1:
		 	local_ntc_value = 19 + local_ntc_rectify_value +COMPENSATION_VALUE;

		 break;

		 case 2:
		 	local_ntc_value = 20 + local_ntc_rectify_value +COMPENSATION_VALUE;

		 break;

       	   }

   break;


   case degree_seven: //zero degree  21~23 degree

         // zero_d =2;
        array_subscript =  Calculate_Display_Temperature_Value(R10K_21_23,7,ntc_t.ntc_res_read_adc_value,3);
       if(array_subscript > 2)array_subscript=2;
       switch(array_subscript){

		 case 0:
		 	local_ntc_value = 21 + local_ntc_rectify_value +COMPENSATION_VALUE;

		 break;

		 case 1:
		 	local_ntc_value = 22 + local_ntc_rectify_value +COMPENSATION_VALUE;

		 break;

		 case 2:
		 	local_ntc_value = 23+ local_ntc_rectify_value +COMPENSATION_VALUE;

		 break;


        }

   break;

   case degree_eight: //24~26 degree
   	   array_subscript =  Calculate_Display_Temperature_Value(R10K_24_26,8,ntc_t.ntc_res_read_adc_value,3);
	   if(array_subscript > 2)array_subscript=2;
	   switch(array_subscript){

		 case 0:
		 	local_ntc_value = 24 + local_ntc_rectify_value + COMPENSATION_VALUE;

		 break;

		 case 1:
		 	local_ntc_value = 25 + local_ntc_rectify_value +COMPENSATION_VALUE;

		 break;

		 case 2:
		 	local_ntc_value = 26 + local_ntc_rectify_value +COMPENSATION_VALUE;

		 break;

		

        }

   break;

   
   case degree_nine : //27~~30 degree

         array_subscript =  Calculate_Display_Temperature_Value(R10K_27_30,9,ntc_t.ntc_res_read_adc_value,4);
		 // HAL_Delay(5);
  		  if(array_subscript > 3)array_subscript=3;
		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 27 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 28 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 2:
			  local_ntc_value = 29 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 3:
			  local_ntc_value = 30 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  
   
		  }

   break;
   
   case degree_ten: //31~~33 degree

         array_subscript =  Calculate_Display_Temperature_Value(R10K_31_33,10,ntc_t.ntc_res_read_adc_value,3);
		 //HAL_Delay(5);
		 if(array_subscript > 2)array_subscript=2;
		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 31 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 32 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  local_ntc_value = 33 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }


   break;

   case degree_eleven : //34 脌~~37 degree
		 array_subscript =  Calculate_Display_Temperature_Value(R10K_34_37,11,ntc_t.ntc_res_read_adc_value,4);
		 if(array_subscript > 3)array_subscript=3;
		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 34 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 35 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  local_ntc_value = 36 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 3:
			  local_ntc_value = 37 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }
   break;
   
   case degree_twelve: //38 ```41 degree
   	     array_subscript =  Calculate_Display_Temperature_Value(R10K_38_41,12,ntc_t.ntc_res_read_adc_value,4);
		 // HAL_Delay(5);
		  if(array_subscript > 3)array_subscript=3;
		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 38 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 39 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  local_ntc_value = 40 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 3:
			  local_ntc_value = 41 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }

   break;
   
   case degree_thirteen ://42 ````44 degree
   	     array_subscript =  Calculate_Display_Temperature_Value(R10K_42_44,13,ntc_t.ntc_res_read_adc_value,3);
		  
		 if(array_subscript > 2)array_subscript=2;

		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 42 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 43 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 2:
			  local_ntc_value = 44 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
   
		  }

   break;

  
   case degree_fourteen : //45````49 degree
   	     array_subscript =  Calculate_Display_Temperature_Value(R10K_45_49,14,ntc_t.ntc_res_read_adc_value,5);
		  //HAL_Delay(5);
		 if(array_subscript > 4)array_subscript=4;
		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 45 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 46+ local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  local_ntc_value = 47 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 3:
			  local_ntc_value = 48 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 4:
			  local_ntc_value = 49 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }

   break;

   
   case degree_fiveteen :  //50````53 degree
   	    array_subscript =  Calculate_Display_Temperature_Value(R10K_50_53,15,ntc_t.ntc_res_read_adc_value,4);
		  //HAL_Delay(5);
		 if(array_subscript > 3)array_subscript=3;
		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 50 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 51 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  local_ntc_value = 52 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 3:
			  local_ntc_value = 53 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }

   break;
   
   case degree_sixteen : //54````58 degree
   	 array_subscript =  Calculate_Display_Temperature_Value(R10K_54_58,16,ntc_t.ntc_res_read_adc_value,5);
	     // HAL_Delay(5);
	      if(array_subscript > 4)array_subscript=4;
		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 54 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 55 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  local_ntc_value = 56 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 3:
			  local_ntc_value = 57 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 4:
			  local_ntc_value = 58 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }

   break;
   
   case  degree_seventeen ://59````64 degree
   		 array_subscript =  Calculate_Display_Temperature_Value(R10K_59_64,17,ntc_t.ntc_res_read_adc_value,6);
		 // HAL_Delay(5);
		  if(array_subscript > 5)array_subscript=5;
		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 59 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 60 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  local_ntc_value = 61 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 3:
			  local_ntc_value = 62 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 4:
			  local_ntc_value = 63 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 5:
			  local_ntc_value = 64 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }

   break;
   
   case degree_eighteen : //65````71 degree
   	   	 array_subscript =  Calculate_Display_Temperature_Value(R10K_65_71,18,ntc_t.ntc_res_read_adc_value,7);
	      if(array_subscript > 6)array_subscript=6;
		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 65 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 66 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  local_ntc_value = 67 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 3:
			  local_ntc_value = 68 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 4:
			  local_ntc_value = 69 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 5:
			  local_ntc_value = 70 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 6:
			  local_ntc_value = 71 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   
   
		  }

   break;

   case degree_nineteen : //72````78 degree
   		 array_subscript =  Calculate_Display_Temperature_Value(R10K_72_78,19,ntc_t.ntc_res_read_adc_value,7);
		//  HAL_Delay(5);
		 if(array_subscript > 6)array_subscript=6;
		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 72 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 73 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  local_ntc_value = 74 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 3:
			  local_ntc_value = 75 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 4:
			  local_ntc_value = 76 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 5:
			  local_ntc_value = 77 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 6:
			  local_ntc_value = 78 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }

   break;
   
   case degree_twenty : //79~85 degree
       array_subscript =  Calculate_Display_Temperature_Value(R10K_79_88,20,ntc_t.ntc_res_read_adc_value,10);
	     //  HAL_Delay(5);
	      if(array_subscript > 9)array_subscript=9;
		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 79 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 80 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  local_ntc_value = 81 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 3:
			  local_ntc_value = 82 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 4:
			  local_ntc_value = 83 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 5:
			  local_ntc_value = 84 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 6:
			  local_ntc_value = 85 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 7:
			  local_ntc_value = 86 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 8:
			  local_ntc_value = 87 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 9:
			  local_ntc_value = 88 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }


   break;

   case degree_twenty_one : //89~100 degree
       array_subscript =  Calculate_Display_Temperature_Value(R10K_89_100,21,ntc_t.ntc_res_read_adc_value,12);
	     //  HAL_Delay(5);
	      if(array_subscript > 11)array_subscript=11;
		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 89 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 90 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  local_ntc_value = 91 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 3:
			  local_ntc_value = 92 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 4:
			  local_ntc_value = 93 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 5:
			  local_ntc_value = 94 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 6:
			  local_ntc_value = 95 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 7:
			  local_ntc_value = 96 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 8:
			  local_ntc_value = 97 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 9:
			  local_ntc_value = 98 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 10:
			  local_ntc_value = 99 + local_ntc_rectify_value +COMPENSATION_VALUE;

		   break;

		    case 11:
			  local_ntc_value = 100 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		  }


   break;

   case degree_twenty_two : //101~118 degree
       array_subscript =  Calculate_Display_Temperature_Value(R10K_101_118,22,ntc_t.ntc_res_read_adc_value,18);
	     //  HAL_Delay(5);
	      if(array_subscript > 17)array_subscript=17;
		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 101+ local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 102 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 2:
			  local_ntc_value = 103 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 3:
			  local_ntc_value = 104 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 4:
			  local_ntc_value = 105 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 5:
			  local_ntc_value = 106 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 6:
			  local_ntc_value = 107 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 7:
			  local_ntc_value = 108 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 8:
			  local_ntc_value = 109 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 9:
			  local_ntc_value = 110 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 10:
			  local_ntc_value = 111 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 11:
			  local_ntc_value = 112 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 12:
			  local_ntc_value = 113 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;
   
		   case 13:
			  local_ntc_value = 114 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 14:
			  local_ntc_value = 115 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 15:
			  local_ntc_value = 116 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		    case 16:
			  local_ntc_value = 117 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		   case 17:
			  local_ntc_value = 118 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		 
   
		  }


   break;

    case degree_twenty_three: //119````120 degree
   	   	 array_subscript =  Calculate_Display_Temperature_Value(R10K_119_120,23,ntc_t.ntc_res_read_adc_value,2);
	     if(array_subscript > 1)array_subscript=1;
		 switch(array_subscript){
   
		   case 0:
			  local_ntc_value = 119 + local_ntc_rectify_value + COMPENSATION_VALUE;
   
		   break;
   
		   case 1:
			  local_ntc_value = 120 + local_ntc_rectify_value +COMPENSATION_VALUE;
   
		   break;

		 }

   }
}
/******************************************************************************
	*
	*Function Name: static uint8_t Calculate_Display_Temperature_Value(const uin16_t *pt,uint8_t length)
	*Function :calculate special value
	*Input Ref: speical transmit display temperature value 
	*Return Ref:NO
	*
******************************************************************************/
static uint8_t Calculate_Display_Temperature_Value(const uint16_t *pt,uint8_t key,uint16_t ntc_res_value,uint8_t length)
{
      uint8_t i;
	  

      for(i=0;i<length;i++){

      if(*(pt+i) ==  ntc_res_value ){

             return i;


      }
     else if(*(pt+i) >  ntc_res_value && (*(pt+i+1) <ntc_res_value)){//high temperature degree is number is smaller

              
               if(i> length) i = length; 
               return i;
				 
          
          }

      }
      return i;

}

/***********************************************************************************************
	*
	*Function Name:uint8_t ntc_res_linear_value(uint8_t ntc_value)
	*Function : display of works time value 
	*Input: NO
	*Return: NO 
	*
*************************************************************************************************/
uint8_t ntc_res_linear_value(uint8_t ntc_value)
{
    
    static uint8_t current_value = 0; // 当前显示值
	
    static uint8_t init_done = 0;
    int16_t diff;


    if (!init_done) {
        current_value = ntc_value;
        init_done = 1;
    }
    

    diff = (int16_t) ntc_value - (int16_t) current_value;

    if (diff > 0 && diff < 6){
    	compare_up_counter++;
    	compare_down_counter=0;
       if(compare_up_counter > 3){
       	  compare_up_counter=0;
          current_value++; // 每次只加 1
        }
    }
	else if( diff > 0 && diff > 5) {

        current_value  = ntc_value ;

	}
    else if (diff < 0) {
    	compare_down_counter++;
    	compare_up_counter=0;
    	if(compare_down_counter > 3){
    	   compare_down_counter=0;
           current_value--; // 每次只减 1
        }
    }
    else if(diff==0){// diff == 0 时，不变
		compare_down_counter=0;
		compare_up_counter=0;
	}

    return current_value;
}






