from statistics import mode
from tkinter import CASCADE
from django.db import models
from django.forms import CharField, NullBooleanField


# Create your models here.

class ESB(models.Model):
    id = models.IntegerField(unique = True, primary_key=True)
    ip = models.CharField(max_length=256, blank=True, null=True)

    def __str__(self):
        return str(self.id)

class Sensor (models.Model):
    name_esbid_type = models.CharField(max_length=200, primary_key=True)
    esb_id = models.ForeignKey(ESB, on_delete=models.CASCADE, blank=False)
    gase = models.CharField(max_length=500, blank=False, null=False)
    def __str__(self):
        return self.name_esbid_type+self.gase

class Daten(models.Model):
    messwert = models.IntegerField(blank=True, null=True) #kaputter Sensor ist -1
    sensor_id = models.ForeignKey(Sensor, on_delete=models.CASCADE, blank=False)
    time_recorded = models.DateTimeField(auto_now_add=True)




