#pragma once

void SRS_EnableVCU(void);
void SRS_EnableMotorDrive(void);
void SRS_EnableEPS(void);
void SRS_EnableEBS(void);
void SRS_EnableCANRelay(void);

void SRS_DisableVCU(void);
void SRS_DisableMotorDrive(void);
void SRS_DisableEPS(void);
void SRS_DisableEBS(void);
void SRS_DisableCANRelay(void);

void Module_InitAll(void);
void Module_ShutDownAll(void);
void Module_StarPowerAll(void);
