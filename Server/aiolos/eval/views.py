from xml.sax import default_parser_list
from django.shortcuts import render,redirect
import json
from eval.models import Sensor, Daten




# Create your views here.
def home(request):
    sen_liste = []
    data_liste = []
    esp_id_liste = []
    esp_id_liste_no_dup = []

    sensors = Sensor.objects.all().order_by('esbid_type')
    print("HALLLOOOOOOOOOOOO")
    print(sensors)
    sensorsZero = sensors.filter(esbid_type__contains='0_')
    sensorsOne = sensors.filter(esbid_type__contains='1_')
    sensorsTwo = sensors.filter(esbid_type__contains='2_')
    sensorsThree = sensors.filter(esbid_type__contains='3_')
    print("=============================================")
    print(sensorsOne)

    datenobj = Daten.objects.all()
    for sen in sensors:
    #     dataset = sen.daten_set.exclude(sensor_id__exact="")
    #     liste.append(dataset)
    # print(liste)
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

            data_liste.append([data.messwert, data.time_recorded])
            #print(esp_num, sen_type, data.messwert)
        sen_liste.append(data_liste)
        data_liste = []

        for i in esp_id_liste:
            if i not in esp_id_liste_no_dup:
                esp_id_liste_no_dup.append(i)

    print("!!!!",esp_id_liste_no_dup)
    print(sen_liste)

    

    return render(request, 'home.html', {"sen_liste": sen_liste, 'esp_id_list_no_dup': esp_id_liste_no_dup, 'sensors': sensors, 'sensorsZero': sensorsZero, 'sensorsOne': sensorsOne, 'sensorsTwo': sensorsTwo, 'sensorsThree': sensorsThree })  #alle ids als liste,   


def feed_data(request):
    # if request=="POST":
    #     receiced_json = request.body.decode('utf-8')
    #     x = json.loads(receiced_json)

    example_json = '{"Node" : 7,"Sensors" : [{"Type": "MQ-2", "Value": 95}, {"Type": "MQ-135", "Value": 70},{"Type": "MQ-8", "Value": 70}, {"Type": "MQ-86", "Value": 70}, {"Type": "MQ-8", "Value": 450}]}'

    x = json.loads(example_json)

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

    return render(request, 'home.html', {})
    


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

