from microdata.models import Device, Event, Appliance, DeviceSettings
from rest_framework import serializers
from home.serializers import UserSerializer

class ApplianceSerializer(serializers.HyperlinkedModelSerializer):
	class Meta:
		model = Appliance
		fields = ('name', 'serial', 'chart_color')

class DeviceSerializer(serializers.HyperlinkedModelSerializer):
   
   class Meta:
      model = Device
      fields = ('owner', 'ip_address', 'secret_key', 'serial', 'name', 'registered','fanout_query_registered')
      

class EventSerializer(serializers.HyperlinkedModelSerializer):
   
   class Meta:
      model = Event
      fields = ('device', 'dataPoints')


class DeviceSettingsSerializer(serializers.ModelSerializer):

	class Meta:
		model = DeviceSettings
		fields = ('device', 'main_channel', 'device_serial')