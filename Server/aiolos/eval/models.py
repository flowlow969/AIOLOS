from statistics import mode
from tkinter import CASCADE
from django.db import models
from django.forms import CharField, NullBooleanField


# Create your models here.



class Sensor (models.Model):
    esbid_type = models.CharField(max_length=200, primary_key=True)
    gase = models.CharField(max_length=500, blank=False, null=False)
    def __str__(self):
        return self.esbid_type

class Daten(models.Model):
    messwert = models.IntegerField(blank=True, null=True) #kaputter Sensor ist -1
    sensor_id = models.ForeignKey(Sensor, on_delete=models.CASCADE, blank=False)
    time_recorded = models.DateTimeField(auto_now_add=True)




