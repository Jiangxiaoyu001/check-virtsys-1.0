Name:check-virtsys		
Version:1.0	
Release:10%{?dist}
Exclusivearch:x86_64
# assign os
Exclusiveos:Linux
Summary:check virtsys tools	
License:GPLv2+	
URL:https://github.com/Jiangxiaoyu001/check-virtsys-1.0
Source0:%{name}-tst-%{version}.tar.gz
Requires(post): desktop-file-utils
Requires(postun): desktop-file-utils	
#Requires: qt5
Requires: qt5-qtcharts
BuildRequires: gcc-c++
BuildRequires: libvirt-glib
BuildRequires: pkgconfig(gthread-2.0) 
BuildRequires: pkgconfig(glib-2.0) >= 2.40
BuildRequires: pkgconfig(libvirt) >= 0.10.0
#BuildRequires: pkgconfig(libvirt-glib)
%description
free tool to custom virtual system 
than it's still in tesing develop

%prep
%setup -q


%build
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
%__make install  DESTDIR=$RPM_BUILD_ROOT

%files
%doc README.md COPYING AUTHORS ChangeLog NEWS
%{_bindir}/%{name}
%{_datadir}/icons/check-virtsys/*
%{_datadir}/qss/*
#%{_datadir}/qss/QListWidget.qss
#%{_datadir}/qss/listwid.qss
%{_datadir}/applications/check-virtsys.desktop

%changelog
* Wed Mar 9 2022 jiangxiaoyu <jiangxiaoyu@work> - 1.0.10
- modify ：custom frameLessWidget to design window ,Now it's in testing

* Mon Oct 18 2021 jiangxiaoyu <jiangchao@nfschina> - 1.0.9
- modify ：添加汉化功能，soc以及虚拟组件

* Fri Aug 20 2021 jiangxiaoyu <jiangchao@nfschina> - 1.0.8
- modify ： 打包发布　V1.0 ，提供给用户使用

* Mon Aug 16 2021 jiangxiaoyu <jiangchao@nfschina> - 1.0.7
- modify ： 使用　C++ 异常捕获处理，捕获获取虚拟系统数据时出现的异常

* Fri Aug 13 2021 jiangxiaoyu <jiangchao@nfschina> - 1.0.6
- modify ： C++ - nullptr replaced C-NULL


* Thu Aug 12 2021 jiangxiaoyu <jiangchao@nfschina> - 1.0.5
- modify ：datail 界面设计


* Wed Aug 04 2021 jiangxiaoyu <jiangchao@nfschina> - 1.0.４
- modify ：处理内存溢出引起的指针错误　

* Wed Aug 04 2021 jiangxiaoyu <jiangchao@nfschina> - 1.0.3
- modify ：处理内存泄漏，Map 中指针释放问题

* Wed Aug 04 2021 jiangxiaoyu <jiangchao@nfschina> - 1.0.２
- modify ：重构代码架构

* Tue Aug 03 2021 jiangxiaoyu <jiangchao@nfschina> - 1.0.１
- modify ：增加定时器，刷新界面

* Mon Aug 02 2021 jiangxiaoyu <jiangchao@nfschina> - 1.0.0
- modify ：增加多线程机制，处理数据



