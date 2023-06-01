/*************************************************************************************************
This is to certify that this project is our own work, based on our personal efforts in studying and
applying the concepts learned. We have constructed the functions and their respective algorithms
and corresponding code by us. The program was run, tested, and debugged by our own efforts. We
further certify that we have not copied in part or whole or otherwise plagiarized the work of other
students and/or persons.

 ASTURIANO, CHRISTIAN EMMANUEL S., DLSU ID# 12126780
 JARDENIL, AARON RANDALL, DLSU ID# 12133604
*************************************************************************************************/
#include <stdio.h>
#include <string.h>
#define MAX_SYMPTOMS 20
#define MAX_IMPRESSIONS 20
typedef char String[101];

struct symptomType
{
    int number;
    String name;
    String question;
};

struct impressionType
{
    int number;
    String name;
    int symptomsPresent[20];
};

struct patientType
{
    String name;
    String number;
    int age;
    char gender;
};

/* findInt finds a specified integer in an array
 @param nArray[] - the array to be searched
 @param nSearchKey - the key to be searched in the array
 @param n - the size of the array
 @return the index of nSearchKey in the array, otherwise return -1
 Pre-condition: all the parameters are valid and all values in array are unique
*/
int
findInt(int nArray[] , 
        int nSearchKey , 
        int n)
{
    int i;
    int isFound = -1;

    i = 0;
    while (nArray[i] != 0 && isFound == -1 && i < n)
    {
        if (nArray[i] == nSearchKey)
            isFound = i;
        i++;
    }

    return isFound;
}

/* lowerCase converts a string to all lowercase letters (if applicable)
 @param pInput - the address of the string to be converted to all lower case
 @param pTemp - the address of the character array to store the converted string
 @return the address of the converted string 
 Pre-condition: pInput contains letters
*/
char 
*lowerCase(char * pInput , 
           char * pTemp)
{
    int i, nLen;
    
    strcpy (pTemp, pInput);
    nLen = strlen(pTemp);
    
    for (i = 0; i < nLen; i++)
    {
        if (pTemp[i] >= 65 && pTemp[i] <= 90)
            pTemp[i] += 32;
    }

    return pTemp;
}

/* createNewList creates a new list of symptoms and impressions in the form of text files
 @param fp - the address of the file container
 @param symptoms[] - array of structs containing details of symptoms
 @param impressions[] - array of structs containing details of impressions
 @param pTotalSymptoms - the address of the total number of symptoms
 @param pTotalImpressions - the address of the total number of impressions
 @return symptoms.txt containing the number of symptoms and symptoms information
 @return impressions.txt containing the number of impressions and impressions information
 Pre-condition: the input values for symptoms and impressions are valid
*/
void
createNewList(FILE * fp , 
              struct symptomType symptoms[] , 
              struct impressionType impressions[] ,
              int * pTotalSymptoms , 
              int * pTotalImpressions)
{
    int nPresentSymps;
    int i, j;

    printf("-----------------\n");

    //input number of symptoms + error handling
    do
    {
        printf("How many symptoms do you want to consider? ");
        scanf("%d", pTotalSymptoms);


        if (!(*pTotalSymptoms >= 1 && *pTotalSymptoms <= 20))
            printf("\nInvalid number of symptoms (only 1-20)\n");
      
    } while (!(*pTotalSymptoms >= 1 && *pTotalSymptoms <= 20));
    
    printf("\n");

    //input symptom details
    for (i = 0; i < *pTotalSymptoms; i++)
    {
        symptoms[i].number = i + 1;
        printf("Symptom # %d\n", symptoms[i].number);
        printf("What is the symptom? ");
        scanf(" %[^\n]%*c", symptoms[i].name);
        printf("How do you want to ask the symptom?\n");
        scanf(" %[^\n]%*c", symptoms[i].question);
        printf("\n");
    }
    printf("\n");

    //write symptoms text file
    fp = fopen("Symptoms.txt", "w");

    fprintf(fp, "%d\n", *pTotalSymptoms);
    
    for(i = 0; i < *pTotalSymptoms; i++)
    {
        fprintf(fp, "%d\n%s\n%s", symptoms[i].number, symptoms[i].name, symptoms[i].question);
        
        if (i != *pTotalSymptoms - 1)
            fprintf(fp, "\n");
    }

    fclose(fp);

    //input number of impressions + error handling
    do
    {
        printf("How many impressions do you want to enter? ");
        scanf("%d", pTotalImpressions);
      
        if (!(*pTotalImpressions >= 1 && *pTotalImpressions <= 20))
            printf("\nInvalid number of impressions (only 1-20)\n"); 
      
    } while (!(*pTotalImpressions >= 1 && *pTotalImpressions <= 20));

    printf("\n");

    //input impression details
    for (i = 0; i < *pTotalImpressions; i++)
    {
        impressions[i].number = i + 1;
        printf("Impression #%d\n", i+1);
      
        printf("What is the illness? ");
        scanf(" %[^\n]%*c", impressions[i].name);
      
        printf("Below is a list of symptoms.\n\n");
        
        for(j = 0; j < *pTotalSymptoms; j++)
            printf("%d. %s\n", j+1, symptoms[j].name);

        //initialize impressions[i].symptomsPresent[] array to remove garbage values
        for (j = 0; j < 20; j++)
            impressions[i].symptomsPresent[j] = 0;
      
        printf("\nHow many of the symptoms above are present in a %s case? ", impressions[i].name);
        scanf("%d", &nPresentSymps);
      
        printf("Enter the corresponding number of each symptom: \n");

        for (j = 0; j < nPresentSymps; j++)
            scanf("%d", &impressions[i].symptomsPresent[j]);
        
        printf("\n");
    }

    //write impressions text file
    fp = fopen("Impressions.txt", "w");

    fprintf(fp, "%d\n", *pTotalImpressions);
    
    for (i = 0; i < *pTotalImpressions; i++)
    {
        fprintf(fp, "%d\n%s\n", impressions[i].number, impressions[i].name);
        for (j = 0; j < 20; j++)
        {
          if (impressions[i].symptomsPresent[j] != 0)
          {
            if (j < 19)
            { 
                if (impressions[i].symptomsPresent[j+1] == 0)
                  fprintf(fp, "%d", impressions[i].symptomsPresent[j]);
                else
                  fprintf(fp, "%d ", impressions[i].symptomsPresent[j]);
            }
            else
                fprintf(fp, "%d", impressions[i].symptomsPresent[j]);
          }
        }
        if (i != *pTotalImpressions-1)  
            fprintf(fp, "\n");
    }   
    
    fclose(fp);
}

/* funcA returns the number of capital letters that are changed to small letters
 @param fp - the address of the file container
 @param symptoms[] - array of structs containing details of symptoms
 @param impressions[] - array of structs containing details of impressions
 @return symptoms[].number - the number of the symptom
 @return symptoms[].name - the name of the symptom
 @return symptoms[].question - the question of the symptom
 @return impressions[].number - the number of the impression
 @return impressions[].name - the name of the impression
 @return impressions[].symptomsPresent[] - the array containing the number of symptoms present in the impression
 Pre-condition: symptoms.txt and impressions.txt files contain the correct format if they exist
*/
void 
useExistingList(FILE * fp , 
                struct symptomType symptoms[] , 
                struct impressionType impressions[] ,
                int * pTotalSymptoms , 
                int * pTotalImpressions)
{
    if (fopen("Symptoms.txt", "r") == NULL || fopen("Impressions.txt", "r") == NULL)
        printf("ERROR: Missing files.\n");
    else
    {
        int i, j;
        char c;

        //read symptoms file (symptoms.txt)
        fp = fopen("Symptoms.txt", "r");

        fscanf(fp, "%d", pTotalSymptoms);

        for (i = 0; i < *pTotalSymptoms; i++)
        {
            fscanf(fp, "%d", &symptoms[i].number);
            fscanf(fp, " %[^\n]%*c", symptoms[i].name);
            fscanf(fp, " %[^\n]%*c", symptoms[i].question);
        }

        //read impressions file (impressions.txt)
        fp = fopen("Impressions.txt", "r");

        //scans the total number of impressions
        fscanf(fp, "%d", pTotalImpressions);

        //scans the impression details
        for (i = 0; i < *pTotalImpressions; i++)
        {
            fscanf(fp, "%d", &impressions[i].number);
            fscanf(fp, " %[^\n]%*c", impressions[i].name);

            //initalize array to get rid of garbage values
            for (j = 0; j < 20; j++)
                impressions[i].symptomsPresent[j] = 0;

            //write the present symptoms for the impression into array
            j = 0;

            while (fscanf(fp, "%d%c", &impressions[i].symptomsPresent[j], &c) == 2 && 
                    j < MAX_SYMPTOMS && c != '\n')
                j++;       
        }
    }
}

/* displaySymptoms displays the present symptoms of a specified impression
 @param symptoms[] - array of structs containing details of symptoms
 @param impressions[] - array of impressions containing details of impressions
 @param nTotalSymptoms - the total number of symptoms
 @param nTotalImpressions - the total number of impressions
 @return print the symptoms present in specified impression
 Pre-condition: useExistingList() was used to scan and initialize necessary data structures prior
*/
void
displaySymptoms(struct symptomType symptoms[] , 
                struct impressionType impressions[] ,
                int nTotalSymptoms , 
                int nTotalImpressions)
{
    String strInput;
    int nCmpVal = 1;
    int i, iCopy;

    printf("-----------------\n");
    
    //checks if the list exists (useExistingList() was used)
    if (nTotalSymptoms == 0 || nTotalImpressions == 0)
        printf("ERROR: Incomplete or Missing List.\n");

    //asks the impression to be displayed + error handling
    else
    {
        printf("What is the impression? ");
        scanf(" %[^\n]%*c", strInput);
    
        for (i = 0; i < nTotalImpressions; i++)
        {
            nCmpVal = strcmp(strInput, impressions[i].name);
            if (!nCmpVal)
            {
                iCopy = i;
                i = nTotalImpressions;
            }
        }
        
        if (nCmpVal)
            printf("Unknown Impression.\n\n");

        //display the symptoms
        else
        {
            printf("Symptoms of %s are:\n", strInput);
        
            i = 0;
            while ((impressions[iCopy].symptomsPresent[i] != 0) && (i < 20))
            {
                printf("    %s\n", symptoms[impressions[iCopy].symptomsPresent[i]-1].name);
                i++;
            } 
        }
    }  
}

/* modifySymptoms modifies the present symptoms of a specified impression
 @param fp - the address of the file container
 @param symptoms[] - array of structs containing details of symptoms
 @param impressions[] - array of structs containing details of impressions
 @param nTotalSymptoms - the total number of symptoms
 @param nTotalImpressions - the total number of impressions
 @return updated impression details stored in impressions[] struct
 Pre-condition: useExistingList() was used to scan and initialize necessary data structures prior
*/
void
modifySymptoms(FILE * fp , 
               struct symptomType symptoms[] , 
               struct impressionType impressions[] ,
               int nTotalSymptoms , 
               int nTotalImpressions)
{
    String strInput;
    int nCmpVal = 1;
    int nPresentSymps;
    int i, j, iCopy;

    printf("-----------------\n");

    //checks if the list exists (useExistingList() was used)
    if (nTotalSymptoms == 0 || nTotalImpressions == 0)
        printf("ERROR: Incomplete or Missing List.\n");

    else
    {   //asks for impression to be modified
        printf("What is the impression? ");
        scanf(" %[^\n]%*c", strInput);

        //search element of the target impression + error handling
        for (i = 0; i < nTotalImpressions; i++)
        {
            nCmpVal = strcmp(strInput, impressions[i].name);
            if (!nCmpVal)
            {
                iCopy = i;
                i = nTotalImpressions;
            }
        }
    
        if (nCmpVal)
            printf("Unknown Impression.\n\n");

        //display symptoms
        else
        {
            printf("Symptoms of %s are:\n", strInput);
        
            i = 0;
            while ((impressions[iCopy].symptomsPresent[i] != 0) && (i < 20))
            {
                printf("    %s\n", symptoms[impressions[iCopy].symptomsPresent[i]-1].name);
                i++;
            } 
            
            printf("\nYou can modify the symptoms of %s.\n", impressions[iCopy].name);
            printf("Below is a list of symptoms.\n\n");
            
            for (i = 0; i < nTotalSymptoms; i++)
                printf("    %d. %s\n", i+1, symptoms[i].name);
            
            //initialize impressions[iCopy].symptomsPresent[] array
            for (j = 0; j < 20; j++)
                impressions[iCopy].symptomsPresent[j] = 0;
            
            //ask the modifications of the symptoms
            do
            {
                printf("\nHow many of the symptoms above are present in a %s case? ", impressions[iCopy].name);
                scanf("%d", &nPresentSymps);
                
                if (!(nPresentSymps >= 1 && nPresentSymps <= 20))
                    printf("\nInvalid number of symptoms (only 1-20)\n");
            } while (!(nPresentSymps >= 1 && nPresentSymps <= 20));
          
            printf("Enter the corresponding number of each symptom: \n");
            for (j = 0; j < nPresentSymps; j++)
                scanf("%d", &impressions[iCopy].symptomsPresent[j]);

            //display the new symptoms
            printf("\nHere are the NEW SYMPTOMS of %s:\n", impressions[iCopy].name);
          
            i = 0;
            while ((impressions[iCopy].symptomsPresent[i] != 0) && (i < 20))
            {
                printf("    %s\n", symptoms[impressions[iCopy].symptomsPresent[i] - 1].name);
                i++;
            } 
        
            //rewrite impressions text file (Impressions.txt)
            fp = fopen("Impressions.txt", "w");
        
            fprintf(fp, "%d\n", nTotalImpressions);
            
            for (i = 0; i < nTotalImpressions; i++)
            {
                fprintf(fp, "%d\n%s\n", impressions[i].number, impressions[i].name);
                for (j = 0; j < 20; j++)
                {
                  if (impressions[i].symptomsPresent[j] != 0)
                  {
                    if (j < 19)
                    { 
                       if (impressions[i].symptomsPresent[j + 1] == 0)
                          fprintf(fp, "%d", impressions[i].symptomsPresent[j]);
                        else
                          fprintf(fp, "%d ", impressions[i].symptomsPresent[j]);
                    }
                    else
                        fprintf(fp, "%d", impressions[i].symptomsPresent[j]);
                           
                  }
                }
                if (i != nTotalImpressions - 1)
                    fprintf(fp, "\n");
            } 
            
            fclose(fp);
        }
      }
}

/* createPatienRecord creates a record for the patients
 @param symptoms[] - array of structs containing details of symptoms
 @param impressions[] - array of structs containing details of impressions
 @param nTotalSymptoms - the total number of symptoms
 @param nTotalImpressions - the total number of impressions
 @return (patient number).txt containing the details, symptoms, and impressions of the patient.
 Pre-condition: useExistingList() was used to scan and initialize necessary data structures prior
*/
void 
createPatientRecord(struct symptomType symptoms[] , 
                    struct impressionType impressions[] , 
                    int nTotalSymptoms , 
                    int nTotalImpressions)
{
    FILE *fp;
    String filename;
    String temp;
    char cAnswer;
    char c;
    struct patientType patient;
    int i, j;
    int patientSymptoms[20] = {}, patientImpressions[20] = {};
    int nSymp = 0, nImp = 0;
    int isLast;
    int allPresent;
    
    if (nTotalSymptoms == 0 || nTotalImpressions == 0)
        printf("ERROR: Incomplete or Missing List.\n");
    else
    {
        //enter patient information
        printf("What is your name? ");
        scanf("  %[^\n]%*c", patient.name);
        
        printf("What is your patient number? ");
        scanf("  %[^\n]%*c", patient.number);
        
        printf("Enter your age: ");
        scanf("%d", &patient.age);
    
        printf("Gender (M/F): ");
        scanf(" %c", &patient.gender);
        
        //ask for Symptoms
        for (i = 0; i < nTotalSymptoms; i++)
        {
            printf("%s ", symptoms[i].question);
            scanf(" %c", &cAnswer);
    
            if (cAnswer == 'y' || cAnswer == 'Y')
            {
                //record present symptoms into array
                patientSymptoms[nSymp] = symptoms[i].number;
                nSymp++;
            }
        }
    
        //write HPI File (patient history of present illness file)
        strcpy(filename, patient.number);
        strcat(filename, ".txt");
        fp = fopen(filename, "w");

        printf("\n");
        fprintf(fp, "History of Present Illness\n\n");
        fprintf(fp, "%s, patient # %s is a %d-year old ", patient.name, patient.number, patient.age);
    
        if (patient.gender == 'M' || patient.gender == 'm')
            fprintf(fp, "male. He has ");
        else
            fprintf(fp, "female. She has ");
    
        //check if there are multiple symptoms for formatting purposes (to add "and" and ",")
        if (nSymp == 1)
        {
            fprintf(fp, "%s", lowerCase(symptoms[patientSymptoms[0] - 1].name, temp));
        }
        else if (nSymp > 1)
        {
            isLast = 0;
            i = 0;
            
            while (i < nSymp && isLast == 0)
            {
                isLast = 1;
                for (j = i + 1; j < nSymp; j++)
                {
                    if (patientSymptoms[j] != 0)
                        isLast = 0;
                }
    
                if (isLast)
                    fprintf(fp, "and %s", lowerCase(symptoms[patientSymptoms[i] - 1].name, temp));
                else if (nSymp == 2)
                    fprintf(fp, "%s ", lowerCase(symptoms[patientSymptoms[i] - 1].name, temp));
                else
                    fprintf(fp, "%s, ", lowerCase(symptoms[patientSymptoms[i] - 1].name, temp));
    
                i++;
            }
        }
        else
            fprintf(fp, "no symptoms");
    
        fprintf(fp, ".");
    
        
    
        //evaluate patient impressions based on present symptoms 
        for (i = 0; i < nTotalImpressions; i++)
        {
            allPresent = 1;
            j = 0;
              
            while (impressions[i].symptomsPresent[j] != 0 && j < nTotalSymptoms)
            {
                //use findInt() to search if all the present symptoms in an impression is present in the patient
                if (findInt(patientSymptoms, impressions[i].symptomsPresent[j], MAX_SYMPTOMS) == -1)
                    allPresent = 0;
                
                j++;
            }
    
            if (allPresent)
            {
               patientImpressions[nImp] = impressions[i].number;
                nImp++;
            }   
        }

        //check if there are multiple impressions for formatting purposes (to add "and" and ",")
        if (nImp == 1)
        {
            fprintf(fp, " Impressions are %s", impressions[patientImpressions[0] - 1].name);
        }
        else if (nImp > 1)
        {
    
            fprintf(fp, " Impressions are ");
            
            isLast = 0;
            i = 0;
            
            while (i < nImp && isLast == 0)
            {
                isLast = 1;
                for (j = i + 1; j < nImp; j++)
                {
                    if (patientImpressions[j] != 0)
                        isLast = 0;
                }
    
                if (isLast)
                    fprintf(fp, "and %s", impressions[patientImpressions[i] - 1].name);
                else if (nImp == 2)
                    fprintf(fp, "%s ", impressions[patientImpressions[i] - 1].name);
                else
                    fprintf(fp, "%s, ", impressions[patientImpressions[i] - 1].name);
    
                i++;
            }
        }
        else
            fprintf(fp, " No impressions found");
    
        fprintf(fp, ".");
    
        fclose(fp);

        fp = fopen(filename, "r");

        while(fscanf(fp, "%c", &c) == 1)
            printf("%c", c);
    }
}

//printMainMenu displays the menu that shows the different user types and the exit option.
void 
printMainMenu()
{
    printf("-----------------\n");
    printf("MENU #1 User Type\n\n");
    printf("D for Doctor\n");
    printf("P for Patient\n");
    printf("E for Exit\n\n"); 
}

//printDoctorMenu displays the menu that show
void
printDoctorMenu()
{
    printf("-----------------\n");
    printf("MENU #2 Doctor\n\n");
    printf("C to Create a new list of symptoms and impressions\n");
    printf("U to Use the existing list of symptoms and impressions\n");
    printf("D to Display Symptoms\n");
    printf("M to Modify Symptoms\n");
    printf("E to Exit\n\n");
}

int 
main() {

    //declare and initialize necessary structs and variables
    FILE *fp = NULL;
    char cChoice1, cChoice2;

    cChoice1 = '\0';
    cChoice2 = '\0';
    
    int nTotalSymptoms = 0, nTotalImpressions = 0;
    struct symptomType symptoms[MAX_SYMPTOMS];
    struct impressionType impressions[MAX_IMPRESSIONS];

    //display menu and let user navigate
    while (cChoice1 != 'E' && cChoice1 != 'e')
    {
        cChoice1 = '\0';
        cChoice2 = '\0';
        printMainMenu();
        printf("Enter your choice: ");
        scanf(" %c", &cChoice1);
        printf("\n");
        
        switch (cChoice1)
        {
        case 'D':
        case 'd':
            while (cChoice2 != 'E' && cChoice2 != 'e' && cChoice2 != 'U' && cChoice2 != 'u')
            {
                printDoctorMenu();
                printf("Enter your choice: ");
                scanf(" %c", &cChoice2);
                switch (cChoice2)
                {
                    case 'C': 
                    case 'c':
                        createNewList(fp, symptoms, impressions, &nTotalSymptoms, &nTotalImpressions);
                        break;
                    case 'U':
                    case 'u':
                        useExistingList(fp, symptoms, impressions, &nTotalSymptoms, &nTotalImpressions);
                        break;
                    case 'D':
                    case 'd':
                        displaySymptoms(symptoms, impressions, nTotalSymptoms, nTotalImpressions);
                        break;
                    case 'M':
                    case 'm':
                        modifySymptoms(fp, symptoms, impressions, nTotalSymptoms, nTotalImpressions);
                        break;
                    case 'E':
                    case 'e':
                        break;
                    default:
                        printf("Invalid input.\n");
                        break;
                }
            }
            break;
        case 'P':
        case 'p':
            createPatientRecord(symptoms, impressions, nTotalSymptoms, nTotalImpressions);
            break;
        case 'E':
        case 'e':
            break;
        default:
            printf("Invalid input.\n");
            break;
        }

        printf("\n");
    }

    return 0;
}