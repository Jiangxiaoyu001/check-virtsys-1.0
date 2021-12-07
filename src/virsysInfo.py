# This Python file uses the following encoding: utf-8

# if__name__ == "__main__":
#     pass

import libvirt

from xml.etree import ElementTree
conn=libvirt.open("qemu:///system")

for id in conn.listDomainsID():
    domain= conn.fromstring(domain.XMLDesc())
    ifaces =tree.findall('devices/interface/target')
    for i in ifaces
        iface=i.get('dev')
        ifaceinfo =domain.interfaceStats(iface)
        print domain.name(), iface.ifaceinfo
conn.close()
