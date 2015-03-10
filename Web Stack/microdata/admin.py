from django.contrib import admin

from microdata.models import Device, Appliance, Event
from webapp.models import DeviceSettings
# Register your models here.

class DeviceSettingsInline(admin.StackedInline):
	model = DeviceSettings
	can_delete = False
	verbose_name_plural = 'devicesettings'

class DeviceAdmin(admin.ModelAdmin):
   list_display = ('name','owner','serial','position','secret_key','registered','fanout_query_registered',)
   search_fields = ('name','serial')
   readonly_fields=('secret_key',)
   inlines = (DeviceSettingsInline,)

class ApplianceAdmin(admin.ModelAdmin):
   list_display = ('name','pk','serial','chart_color',)


#admin.site.unregister(Device)
admin.site.register(Device, DeviceAdmin)
admin.site.register(Appliance, ApplianceAdmin)
admin.site.register(Event)