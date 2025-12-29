/*
i want to make a c project including all the below 
so prepare me a flowchart for the same... 
1.	all new patient record
2.	display all patient record
3.	search patient by id
4.	update patient information
5.	delete patient
6.	classification of patients on the bases of their annual family income
7.	add doctor
8.	display doctor
9.	search doctor
10.	update doctor
11.	delete doctor
12.	classify doctor by specialisation
13.	connect doctor by patients
14.	assign a doctor to a patient – store doctor id inside patient structure – while adding a patient, show available doctors to choose from
15.	billing system with discounts using enum = room, medicines, total charges + discounts – print bill receipt in file
16.	generate unique id automatically – no need to enter patient / doctors id – program increments id automatically
17.	add date of admission and discharge
18.	add room no/ward allocation – general ward/ icu/ private room
19.	patient type – opd/ ipd/ emergency
20.	track patient’s treatment history – diagnosis/ treatment given, medicines prescribed
21.	search filter – search patients by disease/ doctor by specialisation/ age range/ income category
22.	statics dashboard – total patients and doctors/ most common disease / number of income based categories
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLINE 512
#define MASTER_PATIENTS "patients_master.txt"
#define MASTER_DOCTORS "doctors_master.txt"
#define BILLS_MASTER "bills_master.txt"

int nextPatientID = 1;
int nextDoctorID = 1;

void init_system()
{
    FILE *f;
    char line[MAXLINE];
    f = fopen(MASTER_PATIENTS, "r");
    if(f)
    {
        while(fgets(line, sizeof(line), f))
        {
            int id;
            if(sscanf(line, "%d|", &id) == 1)
            {
                if(id >= nextPatientID) nextPatientID = id + 1;
            }
        }
        fclose(f);
    }
    f = fopen(MASTER_DOCTORS, "r");
    if(f)
    {
        while(fgets(line, sizeof(line), f))
        {
            int id;
            if(sscanf(line, "%d|", &id) == 1)
            {
                if(id >= nextDoctorID) nextDoctorID = id + 1;
            }
        }
        fclose(f);
    }
}

void pause_for_enter()
{
    printf("\nPress Enter to continue...");
    getchar();
}

void add_doctor()
{
    char name[128], spec[128], expS[16];
    int exp;
    int id = nextDoctorID++;
    printf("Enter doctor's name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Enter specialisation: ");
    fgets(spec, sizeof(spec), stdin);
    spec[strcspn(spec, "\n")] = 0;
    printf("Enter experience (years): ");
    fgets(expS, sizeof(expS), stdin);
    exp = atoi(expS);
    char fname[128];
    sprintf(fname, "doctor_%d.txt", id);
    FILE *f = fopen(fname, "w");
    if(!f) { printf("Error creating doctor file.\n"); return; }
    fprintf(f, "ID:%d\nName:%s\nSpecialisation:%s\nExperience:%d\n", id, name, spec, exp);
    fclose(f);
    FILE *m = fopen(MASTER_DOCTORS, "a");
    if(m)
    {
        fprintf(m, "%d|%s|%s|%d\n", id, name, spec, exp);
        fclose(m);
    }
    printf("Doctor added with ID %d\n", id);
    pause_for_enter();
}

void display_doctors()
{
    FILE *m = fopen(MASTER_DOCTORS, "r");
    char line[MAXLINE];
    if(!m)
    {
        printf("No doctors found.\n");
        pause_for_enter();
        return;
    }
    printf("ID | Name | Specialisation | Experience\n");
    printf("----------------------------------------------------\n");
    while(fgets(line, sizeof(line), m))
    {
        int id, exp;
        char name[128], spec[128];
        if(sscanf(line, "%d|%127[^|]|%127[^|]|%d", &id, name, spec, &exp) == 4)
        {
            printf("%d | %s | %s | %d\n", id, name, spec, exp);
        }
    }
    fclose(m);
    pause_for_enter();
}

void search_doctor_by_id()
{
    char s[16];
    printf("Enter Doctor ID: ");
    fgets(s, sizeof(s), stdin);
    int id = atoi(s);
    char fname[128];
    sprintf(fname, "doctor_%d.txt", id);
    FILE *f = fopen(fname, "r");
    if(!f)
    {
        printf("Doctor not found.\n");
        pause_for_enter();
        return;
    }
    char line[MAXLINE];
    while(fgets(line, sizeof(line), f))
    {
        printf("%s", line);
    }
    fclose(f);
    pause_for_enter();
}

void update_doctor()
{
    char s[16];
    printf("Enter Doctor ID to update: ");
    fgets(s, sizeof(s), stdin);
    int id = atoi(s);
    char fname[128];
    sprintf(fname, "doctor_%d.txt", id);
    FILE *f = fopen(fname, "r");
    if(!f)
    {
        printf("Doctor not found.\n");
        pause_for_enter();
        return;
    }
    fclose(f);
    char name[128], spec[128], expS[16];
    int exp;
    printf("Enter new name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Enter new specialisation: ");
    fgets(spec, sizeof(spec), stdin);
    spec[strcspn(spec, "\n")] = 0;
    printf("Enter new experience: ");
    fgets(expS, sizeof(expS), stdin);
    exp = atoi(expS);
    f = fopen(fname, "w");
    if(!f) { printf("Error updating doctor file.\n"); return; }
    fprintf(f, "ID:%d\nName:%s\nSpecialisation:%s\nExperience:%d\n", id, name, spec, exp);
    fclose(f);
    FILE *m = fopen(MASTER_DOCTORS, "r");
    FILE *tmp = fopen("doctors_tmp.txt", "w");
    char line[MAXLINE];
    if(m && tmp)
    {
        while(fgets(line, sizeof(line), m))
        {
            int rid, rexp;
            char rname[128], rspec[128];
            if(sscanf(line, "%d|%127[^|]|%127[^|]|%d", &rid, rname, rspec, &rexp) == 4)
            {
                if(rid == id)
                {
                    fprintf(tmp, "%d|%s|%s|%d\n", id, name, spec, exp);
                }
                else
                {
                    fprintf(tmp, "%s", line);
                }
            }
        }
        fclose(m);
        fclose(tmp);
        remove(MASTER_DOCTORS);
        rename("doctors_tmp.txt", MASTER_DOCTORS);
    }
    printf("Doctor updated.\n");
    pause_for_enter();
}

void delete_doctor()
{
    char s[16];
    printf("Enter Doctor ID to delete: ");
    fgets(s, sizeof(s), stdin);
    int id = atoi(s);
    char fname[128];
    sprintf(fname, "doctor_%d.txt", id);
    if(remove(fname) != 0)
    {
        printf("Doctor file not found.\n");
        pause_for_enter();
        return;
    }
    FILE *m = fopen(MASTER_DOCTORS, "r");
    FILE *tmp = fopen("doctors_tmp.txt", "w");
    char line[MAXLINE];
    if(m && tmp)
    {
        while(fgets(line, sizeof(line), m))
        {
            int rid;
            if(sscanf(line, "%d|", &rid) == 1)
            {
                if(rid != id) fprintf(tmp, "%s", line);
            }
        }
        fclose(m);
        fclose(tmp);
        remove(MASTER_DOCTORS);
        rename("doctors_tmp.txt", MASTER_DOCTORS);
    }
    printf("Doctor deleted.\n");
    pause_for_enter();
}

void classify_doctors()
{
    FILE *m = fopen(MASTER_DOCTORS, "r");
    char line[MAXLINE];
    if(!m) { printf("No doctors.\n"); pause_for_enter(); return; }
    printf("Classified by specialisation:\n");
    while(fgets(line, sizeof(line), m))
    {
        int id, exp;
        char name[128], spec[128];
        if(sscanf(line, "%d|%127[^|]|%127[^|]|%d", &id, name, spec, &exp) == 4)
        {
            printf("%s : %s (ID:%d)\n", spec, name, id);
        }
    }
    fclose(m);
    pause_for_enter();
}

void add_patient()
{
    char name[128], ageS[8], disease[128], type[32], incomeS[32], room[64], admDate[64];
    int age, incomeCat = 0;
    int id = nextPatientID++;
    printf("Enter patient name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Enter age: ");
    fgets(ageS, sizeof(ageS), stdin);
    age = atoi(ageS);
    printf("Enter disease/condition: ");
    fgets(disease, sizeof(disease), stdin);
    disease[strcspn(disease, "\n")] = 0;
    printf("Enter patient type (OPD/IPD/Emergency): ");
    fgets(type, sizeof(type), stdin);
    type[strcspn(type, "\n")] = 0;
    printf("Enter admission date (YYYY-MM-DD) or NA: ");
    fgets(admDate, sizeof(admDate), stdin);
    admDate[strcspn(admDate, "\n")] = 0;
    printf("Enter room/ward (ICU/Private/General) or NA: ");
    fgets(room, sizeof(room), stdin);
    room[strcspn(room, "\n")] = 0;
    printf("Enter annual family income (number): ");
    fgets(incomeS, sizeof(incomeS), stdin);
    int income = atoi(incomeS);
    if(income < 200000) incomeCat = 1;
    else if(income < 1000000) incomeCat = 2;
    else incomeCat = 3;
    char fname[128];
    sprintf(fname, "patient_%d.txt", id);
    FILE *f = fopen(fname, "w");
    if(!f) { printf("Error creating patient file.\n"); return; }
    fprintf(f, "ID:%d\nName:%s\nAge:%d\nDisease:%s\nType:%s\nAdmissionDate:%s\nRoom:%s\nIncome:%d\nIncomeCategory:%d\nDoctorID:%d\n", id, name, age, disease, type, admDate, room, income, incomeCat, 0);
    fclose(f);
    FILE *m = fopen(MASTER_PATIENTS, "a");
    if(m)
    {
        fprintf(m, "%d|%s|%d|%s|%d|%d|%s\n", id, name, age, disease, income, 0, type);
        fclose(m);
    }
    printf("Patient added with ID %d\n", id);
    pause_for_enter();
}

void display_patients()
{
    FILE *m = fopen(MASTER_PATIENTS, "r");
    char line[MAXLINE];
    if(!m) { printf("No patients found.\n"); pause_for_enter(); return; }
    printf("ID | Name | Age | Disease | Income | DoctorID | Type\n");
    printf("-----------------------------------------------------------\n");
    while(fgets(line, sizeof(line), m))
    {
        int id, age, income, docid;
        char name[128], disease[128], type[64];
        if(sscanf(line, "%d|%127[^|]|%d|%127[^|]|%d|%d|%63[^\n]", &id, name, &age, disease, &income, &docid, type) >= 6)
        {
            printf("%d | %s | %d | %s | %d | %d | %s\n", id, name, age, disease, income, docid, type);
        }
    }
    fclose(m);
    pause_for_enter();
}

void search_patient_by_id()
{
    char s[16];
    printf("Enter Patient ID: ");
    fgets(s, sizeof(s), stdin);
    int id = atoi(s);
    char fname[128];
    sprintf(fname, "patient_%d.txt", id);
    FILE *f = fopen(fname, "r");
    if(!f) { printf("Patient not found.\n"); pause_for_enter(); return; }
    char line[MAXLINE];
    while(fgets(line, sizeof(line), f))
    {
        printf("%s", line);
    }
    fclose(f);
    pause_for_enter();
}

void update_patient()
{
    char s[16];
    printf("Enter Patient ID to update: ");
    fgets(s, sizeof(s), stdin);
    int id = atoi(s);
    char fname[128];
    sprintf(fname, "patient_%d.txt", id);
    FILE *f = fopen(fname, "r");
    if(!f) { printf("Patient not found.\n"); pause_for_enter(); return; }
    fclose(f);
    char name[128], ageS[8], disease[128], type[32], incomeS[32], room[64], admDate[64];
    int age, income, incomeCat;
    printf("Enter new name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Enter new age: ");
    fgets(ageS, sizeof(ageS), stdin);
    age = atoi(ageS);
    printf("Enter new disease: ");
    fgets(disease, sizeof(disease), stdin);
    disease[strcspn(disease, "\n")] = 0;
    printf("Enter new type (OPD/IPD/Emergency): ");
    fgets(type, sizeof(type), stdin);
    type[strcspn(type, "\n")] = 0;
    printf("Enter new admission date or NA: ");
    fgets(admDate, sizeof(admDate), stdin);
    admDate[strcspn(admDate, "\n")] = 0;
    printf("Enter new room/ward or NA: ");
    fgets(room, sizeof(room), stdin);
    room[strcspn(room, "\n")] = 0;
    printf("Enter new annual family income: ");
    fgets(incomeS, sizeof(incomeS), stdin);
    income = atoi(incomeS);
    if(income < 200000) incomeCat = 1;
    else if(income < 1000000) incomeCat = 2;
    else incomeCat = 3;
    f = fopen(fname, "w");
    if(!f) { printf("Error updating patient file.\n"); return; }
    fprintf(f, "ID:%d\nName:%s\nAge:%d\nDisease:%s\nType:%s\nAdmissionDate:%s\nRoom:%s\nIncome:%d\nIncomeCategory:%d\nDoctorID:%d\n", id, name, age, disease, type, admDate, room, income, incomeCat, 0);
    fclose(f);
    FILE *m = fopen(MASTER_PATIENTS, "r");
    FILE *tmp = fopen("patients_tmp.txt", "w");
    char line[MAXLINE];
    if(m && tmp)
    {
        while(fgets(line, sizeof(line), m))
        {
            int rid, rage, rincome, rdoc;
            char rname[128], rdisease[128], rtype[64];
            if(sscanf(line, "%d|%127[^|]|%d|%127[^|]|%d|%d|%63[^\n]", &rid, rname, &rage, rdisease, &rincome, &rdoc, rtype) >= 6)
            {
                if(rid == id)
                {
                    fprintf(tmp, "%d|%s|%d|%s|%d|%d|%s\n", id, name, age, disease, income, 0, type);
                }
                else
                {
                    fprintf(tmp, "%s", line);
                }
            }
        }
        fclose(m);
        fclose(tmp);
        remove(MASTER_PATIENTS);
        rename("patients_tmp.txt", MASTER_PATIENTS);
    }
    printf("Patient updated.\n");
    pause_for_enter();
}

void delete_patient()
{
    char s[16];
    printf("Enter Patient ID to delete: ");
    fgets(s, sizeof(s), stdin);
    int id = atoi(s);
    char fname[128];
    sprintf(fname, "patient_%d.txt", id);
    if(remove(fname) != 0)
    {
        printf("Patient file not found.\n");
        pause_for_enter();
        return;
    }
    char hist[128];
    sprintf(hist, "patient_%d_history.txt", id);
    remove(hist);
    FILE *m = fopen(MASTER_PATIENTS, "r");
    FILE *tmp = fopen("patients_tmp.txt", "w");
    char line[MAXLINE];
    if(m && tmp)
    {
        while(fgets(line, sizeof(line), m))
        {
            int rid;
            if(sscanf(line, "%d|", &rid) == 1)
            {
                if(rid != id) fprintf(tmp, "%s", line);
            }
        }
        fclose(m);
        fclose(tmp);
        remove(MASTER_PATIENTS);
        rename("patients_tmp.txt", MASTER_PATIENTS);
    }
    printf("Patient deleted.\n");
    pause_for_enter();
}

void classify_patients_by_income()
{
    FILE *m = fopen(MASTER_PATIENTS, "r");
    char line[MAXLINE];
    if(!m) { printf("No patients.\n"); pause_for_enter(); return; }
    printf("Income Category 1 (Low):\n");
    rewind(m);
    while(fgets(line, sizeof(line), m))
    {
        int id, age, income, docid;
        char name[128], disease[128], type[64];
        if(sscanf(line, "%d|%127[^|]|%d|%127[^|]|%d|%d|%63[^\n]", &id, name, &age, disease, &income, &docid, type) >= 6)
        {
            if(income < 200000) printf("%d | %s | %d | %s\n", id, name, age, disease);
        }
    }
    printf("\nIncome Category 2 (Middle):\n");
    rewind(m);
    while(fgets(line, sizeof(line), m))
    {
        int id, age, income, docid;
        char name[128], disease[128], type[64];
        if(sscanf(line, "%d|%127[^|]|%d|%127[^|]|%d|%d|%63[^\n]", &id, name, &age, disease, &income, &docid, type) >= 6)
        {
            if(income >= 200000 && income < 1000000) printf("%d | %s | %d | %s\n", id, name, age, disease);
        }
    }
    printf("\nIncome Category 3 (High):\n");
    rewind(m);
    while(fgets(line, sizeof(line), m))
    {
        int id, age, income, docid;
        char name[128], disease[128], type[64];
        if(sscanf(line, "%d|%127[^|]|%d|%127[^|]|%d|%d|%63[^\n]", &id, name, &age, disease, &income, &docid, type) >= 6)
        {
            if(income >= 1000000) printf("%d | %s | %d | %s\n", id, name, age, disease);
        }
    }
    fclose(m);
    pause_for_enter();
}

void assign_doctor_to_patient()
{
    char sp[16];
    printf("Enter Patient ID to assign doctor: ");
    fgets(sp, sizeof(sp), stdin);
    int pid = atoi(sp);
    char pfname[128];
    sprintf(pfname, "patient_%d.txt", pid);
    FILE *pf = fopen(pfname, "r");
    if(!pf) { printf("Patient not found.\n"); pause_for_enter(); return; }
    fclose(pf);
    display_doctors();
    char sd[16];
    printf("Enter Doctor ID to assign: ");
    fgets(sd, sizeof(sd), stdin);
    int did = atoi(sd);
    char dfname[128];
    sprintf(dfname, "doctor_%d.txt", did);
    FILE *df = fopen(dfname, "r");
    if(!df) { printf("Doctor not found.\n"); pause_for_enter(); return; }
    fclose(df);
    char line[MAXLINE];
    FILE *f = fopen(pfname, "r");
    FILE *tmp = fopen("patient_update_tmp.txt", "w");
    if(f && tmp)
    {
        while(fgets(line, sizeof(line), f))
        {
            if(strncmp(line, "DoctorID:", 9) == 0)
            {
                fprintf(tmp, "DoctorID:%d\n", did);
            }
            else fprintf(tmp, "%s", line);
        }
        fclose(f);
        fclose(tmp);
        remove(pfname);
        rename("patient_update_tmp.txt", pfname);
    }
    FILE *m = fopen(MASTER_PATIENTS, "r");
    FILE *mt = fopen("patients_tmp.txt", "w");
    if(m && mt)
    {
        while(fgets(line, sizeof(line), m))
        {
            int id, age, income, docid;
            char name[128], disease[128], type[64];
            if(sscanf(line, "%d|%127[^|]|%d|%127[^|]|%d|%d|%63[^\n]", &id, name, &age, disease, &income, &docid, type) >= 6)
            {
                if(id == pid) fprintf(mt, "%d|%s|%d|%s|%d|%d|%s\n", id, name, age, disease, income, did, type);
                else fprintf(mt, "%s", line);
            }
        }
        fclose(m);
        fclose(mt);
        remove(MASTER_PATIENTS);
        rename("patients_tmp.txt", MASTER_PATIENTS);
    }
    printf("Doctor %d assigned to patient %d\n", did, pid);
    pause_for_enter();
}

void add_treatment_history()
{
    char sp[16];
    printf("Enter Patient ID to add treatment entry: ");
    fgets(sp, sizeof(sp), stdin);
    int pid = atoi(sp);
    char pfname[128];
    sprintf(pfname, "patient_%d.txt", pid);
    FILE *pf = fopen(pfname, "r");
    if(!pf) { printf("Patient not found.\n"); pause_for_enter(); return; }
    fclose(pf);
    char entry[256];
    printf("Enter treatment entry text: ");
    fgets(entry, sizeof(entry), stdin);
    entry[strcspn(entry, "\n")] = 0;
    char histname[128];
    sprintf(histname, "patient_%d_history.txt", pid);
    FILE *h = fopen(histname, "a");
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    fprintf(h, "%04d-%02d-%02d %02d:%02d:%02d | %s\n", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, entry);
    fclose(h);
    printf("Treatment entry added.\n");
    pause_for_enter();
}

void view_treatment_history()
{
    char sp[16];
    printf("Enter Patient ID to view history: ");
    fgets(sp, sizeof(sp), stdin);
    int pid = atoi(sp);
    char histname[128];
    sprintf(histname, "patient_%d_history.txt", pid);
    FILE *h = fopen(histname, "r");
    char line[MAXLINE];
    if(!h) { printf("No history found.\n"); pause_for_enter(); return; }
    while(fgets(line, sizeof(line), h))
    {
        printf("%s", line);
    }
    fclose(h);
    pause_for_enter();
}

void calculate_bill()
{
    char sp[16];
    printf("Enter Patient ID for billing: ");
    fgets(sp, sizeof(sp), stdin);
    int pid = atoi(sp);
    char pfname[128];
    sprintf(pfname, "patient_%d.txt", pid);
    FILE *pf = fopen(pfname, "r");
    if(!pf) { printf("Patient not found.\n"); pause_for_enter(); return; }
    fclose(pf);
    char roomsS[32], medS[32], treatS[32], discS[16];
    double roomC, medC, treatC, discount;
    printf("Enter room charges: ");
    fgets(roomsS, sizeof(roomsS), stdin);
    roomC = atof(roomsS);
    printf("Enter medicines charges: ");
    fgets(medS, sizeof(medS), stdin);
    medC = atof(medS);
    printf("Enter treatment/other charges: ");
    fgets(treatS, sizeof(treatS), stdin);
    treatC = atof(treatS);
    printf("Enter discount percentage (0-100): ");
    fgets(discS, sizeof(discS), stdin);
    discount = atof(discS);
    double subtotal = roomC + medC + treatC;
    double total = subtotal * (1.0 - discount/100.0);
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char billname[128];
    sprintf(billname, "bill_%d_%04d%02d%02d%02d%02d%02d.txt", pid, tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    FILE *b = fopen(billname, "w");
    if(!b) { printf("Error creating bill file.\n"); return; }
    fprintf(b, "PatientID:%d\nRoomCharges:%.2f\nMedicines:%.2f\nTreatmentCharges:%.2f\nDiscount:%.2f\nTotal:%.2f\nDate:%04d-%02d-%02d %02d:%02d:%02d\n", pid, roomC, medC, treatC, discount, total, tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    fclose(b);
    FILE *bm = fopen(BILLS_MASTER, "a");
    if(bm)
    {
        fprintf(bm, "%s|%d|%.2f\n", billname, pid, total);
        fclose(bm);
    }
    printf("Bill generated: %s\nTotal: %.2f\n", billname, total);
    pause_for_enter();
}

void search_patients_by_disease()
{
    char disease[128];
    printf("Enter disease to search: ");
    fgets(disease, sizeof(disease), stdin);
    disease[strcspn(disease, "\n")] = 0;
    FILE *m = fopen(MASTER_PATIENTS, "r");
    char line[MAXLINE];
    int found = 0;
    if(!m) { printf("No patients.\n"); pause_for_enter(); return; }
    while(fgets(line, sizeof(line), m))
    {
        int id, age, income, docid;
        char name[128], rdisease[128], type[64];
        if(sscanf(line, "%d|%127[^|]|%d|%127[^|]|%d|%d|%63[^\n]", &id, name, &age, rdisease, &income, &docid, type) >= 6)
        {
            if(strcasecmp(rdisease, disease) == 0)
            {
                printf("%d | %s | %d | %s\n", id, name, age, rdisease);
                found = 1;
            }
        }
    }
    if(!found) printf("No patients with disease %s found.\n", disease);
    fclose(m);
    pause_for_enter();
}

void search_doctors_by_specialisation()
{
    char spec[128];
    printf("Enter specialisation to search: ");
    fgets(spec, sizeof(spec), stdin);
    spec[strcspn(spec, "\n")] = 0;
    FILE *m = fopen(MASTER_DOCTORS, "r");
    char line[MAXLINE];
    int found = 0;
    if(!m) { printf("No doctors.\n"); pause_for_enter(); return; }
    while(fgets(line, sizeof(line), m))
    {
        int id, exp;
        char name[128], rspec[128];
        if(sscanf(line, "%d|%127[^|]|%127[^|]|%d", &id, name, rspec, &exp) == 4)
        {
            if(strcasecmp(rspec, spec) == 0)
            {
                printf("%d | %s | %s | %d\n", id, name, rspec, exp);
                found = 1;
            }
        }
    }
    if(!found) printf("No doctors with specialisation %s found.\n", spec);
    fclose(m);
    pause_for_enter();
}

void search_by_age_range()
{
    char a1s[16], a2s[16];
    printf("Enter min age: ");
    fgets(a1s, sizeof(a1s), stdin);
    printf("Enter max age: ");
    fgets(a2s, sizeof(a2s), stdin);
    int a1 = atoi(a1s);
    int a2 = atoi(a2s);
    FILE *m = fopen(MASTER_PATIENTS, "r");
    char line[MAXLINE];
    int found = 0;
    if(!m) { printf("No patients.\n"); pause_for_enter(); return; }
    while(fgets(line, sizeof(line), m))
    {
        int id, age, income, docid;
        char name[128], disease[128], type[64];
        if(sscanf(line, "%d|%127[^|]|%d|%127[^|]|%d|%d|%63[^\n]", &id, name, &age, disease, &income, &docid, type) >= 6)
        {
            if(age >= a1 && age <= a2)
            {
                printf("%d | %s | %d | %s\n", id, name, age, disease);
                found = 1;
            }
        }
    }
    if(!found) printf("No patients in age range.\n");
    fclose(m);
    pause_for_enter();
}

void search_by_income_category()
{
    char s[8];
    printf("Enter income category (1=Low,2=Middle,3=High): ");
    fgets(s, sizeof(s), stdin);
    int cat = atoi(s);
    FILE *m = fopen(MASTER_PATIENTS, "r");
    char line[MAXLINE];
    int found = 0;
    if(!m) { printf("No patients.\n"); pause_for_enter(); return; }
    while(fgets(line, sizeof(line), m))
    {
        int id, age, income, docid;
        char name[128], disease[128], type[64];
        if(sscanf(line, "%d|%127[^|]|%d|%127[^|]|%d|%d|%63[^\n]", &id, name, &age, disease, &income, &docid, type) >= 6)
        {
            int ic = (income < 200000) ? 1 : ((income < 1000000) ? 2 : 3);
            if(ic == cat)
            {
                printf("%d | %s | %d | %s | %d\n", id, name, age, disease, income);
                found = 1;
            }
        }
    }
    if(!found) printf("No patients in that income category.\n");
    fclose(m);
    pause_for_enter();
}

void statistics_dashboard()
{
    FILE *mp = fopen(MASTER_PATIENTS, "r");
    FILE *md = fopen(MASTER_DOCTORS, "r");
    char line[MAXLINE];
    int pc = 0, dc = 0;
    if(mp)
    {
        while(fgets(line, sizeof(line), mp)) pc++;
        fclose(mp);
    }
    if(md)
    {
        while(fgets(line, sizeof(line), md)) dc++;
        fclose(md);
    }
    printf("Total Patients: %d\nTotal Doctors: %d\n", pc, dc);
    FILE *m = fopen(MASTER_PATIENTS, "r");
    if(!m) { pause_for_enter(); return; }
    char disease[128];
    struct DiseaseCount { char name[128]; int count; } items[256];
    int itemc = 0;
    while(fgets(line, sizeof(line), m))
    {
        int id, age, income, docid;
        char name[128], rdisease[128], type[64];
        if(sscanf(line, "%d|%127[^|]|%d|%127[^|]|%d|%d|%63[^\n]", &id, name, &age, rdisease, &income, &docid, type) >= 6)
        {
            int found = 0;
            for(int i=0;i<itemc;i++)
            {
                if(strcasecmp(items[i].name, rdisease) == 0)
                {
                    items[i].count++;
                    found = 1;
                    break;
                }
            }
            if(!found)
            {
                strcpy(items[itemc].name, rdisease);
                items[itemc].count = 1;
                itemc++;
            }
        }
    }
    fclose(m);
    int maxc = 0, maxi = -1;
    for(int i=0;i<itemc;i++)
    {
        if(items[i].count > maxc) { maxc = items[i].count; maxi = i; }
    }
    if(maxi >= 0) printf("Most common disease: %s (%d patients)\n", items[maxi].name, items[maxi].count);
    else printf("Most common disease: N/A\n");
    int cat1=0, cat2=0, cat3=0;
    m = fopen(MASTER_PATIENTS, "r");
    if(m)
    {
        while(fgets(line, sizeof(line), m))
        {
            int id, age, income, docid;
            char name[128], rdisease[128], type[64];
            if(sscanf(line, "%d|%127[^|]|%d|%127[^|]|%d|%d|%63[^\n]", &id, name, &age, rdisease, &income, &docid, type) >= 6)
            {
                if(income < 200000) cat1++;
                else if(income < 1000000) cat2++;
                else cat3++;
            }
        }
        fclose(m);
    }
    printf("Income categories: Low=%d Middle=%d High=%d\n", cat1, cat2, cat3);
    pause_for_enter();
}

void patient_module()
{
    while(1)
    {
        printf("\nPATIENT MENU\n1. Add New Patient\n2. Display Patients\n3. Search by ID\n4. Update\n5. Delete\n6. Classify by Income\n7. Assign Doctor\n8. Treatment History\n9. Back to Main Menu\nChoice: ");
        char s[8];
        fgets(s, sizeof(s), stdin);
        int c = atoi(s);
        if(c == 1) add_patient();
        else if(c == 2) display_patients();
        else if(c == 3) search_patient_by_id();
        else if(c == 4) update_patient();
        else if(c == 5) delete_patient();
        else if(c == 6) classify_patients_by_income();
        else if(c == 7) assign_doctor_to_patient();
        else if(c == 8)
        {
            printf("1. Add Entry\n2. View History\nChoice: ");
            char ss[8];
            fgets(ss, sizeof(ss), stdin);
            int ch = atoi(ss);
            if(ch == 1) add_treatment_history();
            else view_treatment_history();
        }
        else if(c == 9) break;
        else printf("Invalid choice.\n");
    }
}

void doctor_module()
{
    while(1)
    {
        printf("\nDOCTOR MENU\n1. Add Doctor\n2. Display Doctors\n3. Search by ID\n4. Update\n5. Delete\n6. Classify by Specialisation\n7. Back to Main Menu\nChoice: ");
        char s[8];
        fgets(s, sizeof(s), stdin);
        int c = atoi(s);
        if(c == 1) add_doctor();
        else if(c == 2) display_doctors();
        else if(c == 3) search_doctor_by_id();
        else if(c == 4) update_doctor();
        else if(c == 5) delete_doctor();
        else if(c == 6) classify_doctors();
        else if(c == 7) break;
        else printf("Invalid choice.\n");
    }
}

void billing_module()
{
    while(1)
    {
        printf("\nBILLING MENU\n1. Generate Bill\n2. Back to Main Menu\nChoice: ");
        char s[8];
        fgets(s, sizeof(s), stdin);
        int c = atoi(s);
        if(c == 1) calculate_bill();
        else if(c == 2) break;
        else printf("Invalid choice.\n");
    }
}

void search_filter_module()
{
    while(1)
    {
        printf("\nSEARCH/FILTER MENU\n1. Search Patients by Disease\n2. Search Doctors by Specialisation\n3. Search by Age Range\n4. Search by Income Category\n5. Back to Main Menu\nChoice: ");
        char s[8];
        fgets(s, sizeof(s), stdin);
        int c = atoi(s);
        if(c == 1) search_patients_by_disease();
        else if(c == 2) search_doctors_by_specialisation();
        else if(c == 3) search_by_age_range();
        else if(c == 4) search_by_income_category();
        else if(c == 5) break;
        else printf("Invalid choice.\n");
    }
}

int main()
{
    init_system();
    while(1)
    {
        printf("\nMAIN MENU\n1. Patient Module\n2. Doctor Module\n3. Billing System\n4. Search / Filters\n5. Statistics Dashboard\n6. Exit\nChoice: ");
        char s[8];
        fgets(s, sizeof(s), stdin);
        int c = atoi(s);
        if(c == 1) patient_module();
        else if(c == 2) doctor_module();
        else if(c == 3) billing_module();
        else if(c == 4) search_filter_module();
        else if(c == 5) statistics_dashboard();
        else if(c == 6)
        {
            printf("Saving and exiting...\n");
            break;
        }
        else printf("Invalid choice.\n");
    }
    return 0;
}