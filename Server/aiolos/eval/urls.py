from django.urls import path
from . import views
from django.conf import settings
from django.conf.urls.static import static

urlpatterns = [

    path('', views.home, name='home'),
    path('', views.home, name='home'),
    path('feed_data', views.feed_data, name='feed_data'),




]