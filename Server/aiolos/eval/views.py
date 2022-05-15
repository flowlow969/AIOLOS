from xml.sax import default_parser_list
from django.shortcuts import render,redirect
import json
from eval.models import Sensor, Daten
from django.views.decorators.csrf import csrf_exempt
from django.http import HttpResponse



# Create your views here.
def home(request):
    sen_liste = []
    data_liste = []
    esp_id_liste = []
    esp_id_liste_no_dup = []

    ampellist = []
    
    schwellewerte_kohlenstoffmonoxid = [800, 1400]

    sensors = Sensor.objects.all().order_by('esbid_type')
    
   
    sensorsZero = sensors.filter(esbid_type__contains='0_')
    sensorsOne = sensors.filter(esbid_type__contains='1_')
    sensorsTwo = sensors.filter(esbid_type__contains='2_')
    sensorsThree = sensors.filter(esbid_type__contains='3_')


    datenobj = Daten.objects.all()
    s_flag = 0
    schwell_flag = 1
    for sen in sensors:
      
        dataset = sen.daten_set.all()
 
        flag = 0
        for data in dataset:
            sen_info = sen.esbid_type.split("_")
            esp_num = int(sen_info[0])
            sen_type = sen_info[1]

            if flag == 0:
                data_liste.append(esp_num)
                data_liste.append(sen_type)
                data_liste.append(sen.gase)
                esp_id_liste.append(esp_num)
                flag = 1


            schwellwert = get_schwellwert(sen_type)
            if schwellwert - data.messwert > 0:
                ampel = 0
                
            else:
                ampel = 1
                schwell_flag = 1
                if s_flag == 1:

                    schwell_flag = 0
                    s_flag = 1
                 
            data_liste.append([data.messwert, data.time_recorded])
    
        sen_liste.append(data_liste)
        ampellist.append([sen.esbid_type,ampel, schwell_flag])
        
        
        print(ampellist)
        data_liste = []
        

        for i in esp_id_liste:
            if i not in esp_id_liste_no_dup:
                esp_id_liste_no_dup.append(i)


    print(ampellist)
    first = "0_MQ-135"
    second = "1_MQ-135"
    third = "2_MQ-4"
    fourth = "3_MQ-135"



    for element in ampellist:
        if "0" in element[0]:
            if element[1] == 0:
                continue
            elif element[1] == 1:
                ampellist[0][2] = 1

        if "1" in element[0]:
            if element[1] == 0:
                continue
            elif element[1] == 1:
                ampellist[2][2] = 1

        if "2" in element[0]:
            if element[1] == 0:
                continue
            elif element[1] == 1:
                ampellist[5][2] = 1

        if "3" in element[0]:
            if element[1] == 0:
                continue
            elif element[1] == 1:
               ampellist[8][2] = 1


    print(ampellist)




    return render(request, 'home.html', {"sen_liste": sen_liste, 'esp_id_list_no_dup': esp_id_liste_no_dup, 'sensors': sensors, 'sensorsZero': sensorsZero, 'sensorsOne': sensorsOne, 'sensorsTwo': sensorsTwo, 'sensorsThree': sensorsThree, 'ampellist' : ampellist })  #alle ids als liste,   


@csrf_exempt
def feed_data(request):

    x = json.loads(request.body)

    node = x["Node"]
    for i in range(len(x["Sensors"])):
        type = x["Sensors"][i]["Type"]
        value = x["Sensors"][i]["Value"]
        priv_key = str(node)+"_"+type
        gase=get_gas(type)
        if gase is not "Unknown":

            if Sensor.objects.filter(esbid_type = priv_key).exists()==False:
                sen_to_save = Sensor(esbid_type = priv_key, gase=get_gas(type))
                sen_to_save.save()
            

            data_to_save = Daten(messwert=value, sensor_id = Sensor.objects.get(pk = priv_key))
            data_to_save.save() 
        else:
            print("The Sensor", type, "is not known")   

    return HttpResponse("Data saved")
    


def get_gas(type_gas):
    try:
        return {
                'MQ-2': "LPG, i-Butan, Propan, Methan, Alkohol, Wasserstoff, Rauch",
                'MQ-3': "Alkohol, Ethanol",
                'MQ-4': "Methan, CNG",
                'MQ-5': "LPG",
                'MQ-6': "LPG, Butan",
                'MQ-7': "Kohlenstoffmonoxid",
                'MQ-8': "Wasserstoff",
                'MQ-9': "Kohlenstoffmonoxid",
                'MQ-135': "Benzol, Alkohol, Rauch",

        }[type_gas]
    except KeyError:
        return "Unknown"


def get_schwellwert(gas_schwellwert):
    try:
        return {
                'MQ-2': 10000,
                'MQ-3': 7000,
                'MQ-4': 1500,
                'MQ-5': 7500,
                'MQ-6': 7500,
                'MQ-7': 200,
                'MQ-8': 800,
                'MQ-9': 200,
                'MQ-135': 800,

        }[gas_schwellwert]
    except KeyError:
        return 0
