


void init_Coulomb_counter(void (*Fcc_Updated_calling_fun)(unsigned int, unsigned char), unsigned int design_capacity_mAH);
void SetADCValuesToCoulombCounterFunc(unsigned int adc_dsg_i,unsigned int adc_chg_i,unsigned int adc_vbat,unsigned int adc_ntc1);
void SetFactorValuesToCoulombCounterFunc(float dsg_factor, float chg_factor, float vbat_factor);
void Discharge_capacity(float ocv_percent);
unsigned int get_RM();
unsigned int get_percentage();
unsigned int get_FCC();
//void current_coulomb_counter(unsigned int real_dsg_i,unsigned int real_chg_i,unsigned int real_vbat,unsigned int real_ntc1, unsigned current_status);
void current_coulomb_counter(unsigned current_status);
void FCC_update_EX();

