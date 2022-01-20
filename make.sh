############# coustom user ---------- Jiangxiaoyu 2021-10-18


install_target: first FORCE
	@test -d $(DESTDIR)/usr/bin || mkdir -p $(DESTDIR)/usr/bin
	$(COPY) $(QMAKE_TARGET) $(DESTDIR)/usr/bin/$(QMAKE_TARGET)
	
uninstall_target: FORCE
	-$(DEL_FILE) $(INSTALL_ROOT)/usr/bin/$(QMAKE_TARGET)

install_resource: first FORCE
	@test -d $(DESTDIR)/usr/share/qss   || mkdir -p $(DESTDIR)/usr/share/qss
	@test -d $(DESTDIR)/usr/share/icons || mkdir -p $(DESTDIR)/usr/share/icons
	-$(COPY) /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/icons  $(DESTDIR)/usr/share/icons/$(QMAKE_TARGET)
	-$(COPY) /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/resource/QListWidget.qss $(DESTDIR)/usr/share/qss/QListWidget.qss
	-$(COPY) /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/src/resource/listwid.qss $(DESTDIR)/usr/share/qss/listwid.qss


uninstall_resource: FORCE
	-$(DEL_FILE) $(INSTALL_ROOT)/usr/share/icons/check-virtsys/*
	-$(DEL_FILE) $(INSTALL_ROOT)/usr/share/qss/QListWidget.qss
	-$(DEL_FILE) $(INSTALL_ROOT)/usr/share/qss/listwid.qss
	#-$(DEL_DIR) $(INSTALL_ROOT)/usr/share/qss
	-$(DEL_DIR) $(INSTALL_ROOT)/usr/share/icons/check-virtsys


install_desktop: first FORCE
	@test -d $(DESTDIR)/usr/share/applications/ || mkdir -p $(DESTDIR)/usr/share/applications/
	-$(COPY) /home/jiangxiaoyu/rpmbuild/SOURCES/check-virtsys-1.0/data/check-virtsys.desktop $(DESTDIR)/usr/share/applications/check-virtsys.desktop


uninstall_desktop: FORCE
	-$(DEL_FILE) $(INSTALL_ROOT)/usr/share/applications/check-virtsys.desktop

install: install_target install_resource install_desktop  FORCE

uninstall: uninstall_target uninstall_resource uninstall_desktop  FORCE

FORCE:
