## Dies ist nur eine Übersetztung des Originals von [I-Rinka](https://github.com/I-Rinka)

Ich bin nicht für die funktion zuständig nur für die übersetzung aller Komentare ins Deutsche.

Übersetzung des Originals:
## Win Keyboard Locker

Sind Sie im Online-Unterricht🎓 schon einmal auf ein solches Problem gestoßen?
Wenn Sie sich Lernmaterial ansehen oder nach dem Unterricht die vom Lehrer zugewiesenen Hausaufgaben erledigen, können Sie nicht anders, als das Buch 📖 oder das Notizbuch 📔 auf die Tastatur des Laptops 💻 zu legen, was zu allen möglichen Berührungsproblemen führt 😰.
Versuchen Sie es doch mal mit dieser App.
Win Keyboard Locker, man kann ihn auch Win Keyboard Locker nennen 🔐. Es ist ein leichtgewichtiges Open-Source-Applet. Damit kann man den Computer zum Lernen benutzen, ohne sich Sorgen über versehentliche Berührungen zu machen 🎉.
Wenn das Programm läuft, wird die Tastatur gesperrt, aber die ✅Maus oder das ✅Touchpad funktionieren weiterhin. Auf diese Weise können Sie problemlos mit einigen notwendigen Browsing-Vorgängen fortfahren.

Übersetzt mit DeepL.com (kostenlose Version)
## Install

Die Software ist sehr einfach zu bedienen, und ich bin sicher, dass Sie sofort wissen, wie sie zu benutzen ist, sobald sie geöffnet wird.

## Feature

Sie können die Tastatur wie folgt entsperren und sperren:

**Doppelklick mit der linken Maustaste** auf das Symbol in der Taskleiste
+ Klicken Sie mit der rechten Maustaste auf das Symbol in der Taskleiste und folgen Sie dem Menü, um es zu sperren/entsperren
+ Entsperren **Sie die Tastatur über die Benachrichtigungsschaltfläche** in der Benachrichtigungszentrale

## Uninstall

Aufgrund der Einschränkung der Verwendung von WinRT api, muss das Programm eine AppUserModelId nach der Ausführung zu registrieren; wenn Sie die Benachrichtigung verwenden möchten, müssen Sie win32 haben eine Verknüpfung im Startmenü, so dass dieses Programm ist so eingestellt, eine Verknüpfung im Startmenü automatisch nach der Ausführung zu erstellen.

Da es sich bei diesem Programm nicht um ein Installationsprogramm handelt, hilft es nicht, wenn Sie das Programm deinstallieren und die Verknüpfung im Startmenü entfernen möchten, indem Sie mit der rechten Maustaste auf das Symbol klicken und auf **Deinstallieren** klicken. Richtige Aktion: Rechtsklick auf das Symbol 👉Mehr👉Dateispeicherort öffnen👉Löschen



## Misc 
## Rückständiger Aktualisierungsplan

Der ursprüngliche Autor aktualisiert die Software aufgrund seines Studiums nicht regelmäßig, aber es gibt immer noch ein paar Probleme, die in der aktuellen Version behoben werden müssen

### Optimierungsbedarf:

+ Die Anwendung darf nur einmal gestartet werden, damit die Benutzer sie nicht mehr als einmal gleichzeitig ausführen können.
+ Ich hatte vor, ausschließlich Toast zu verwenden, aber es stellte sich heraus, dass es verwirrend und nicht so natürlich ist wie die aktuelle Mischung aus Toast und NOTIFYICON.
+ Sorgen Sie dafür, dass die Anwendung maximal eine Benachrichtigung zur gleichen Zeit anzeigt.
+ Einige Tastenkombinationen können auch bei gesperrter Tastatur verwendet werden, z.B. Win+A, um die Benachrichtigungszentrale aufzurufen, Vier-Finger-Druck auf dem Trackpad, um die Benachrichtigungszentrale zu öffnen.

### Hinzufügende Funktionen:

+ Benutzerdefinierte Tasten sperren.
+ Umschalten zwischen „Toast-Benachrichtigungen und herkömmlichen Win32-Benachrichtigungen“ ermöglichen.
+ ....
+ Die Notwendigkeit zusätzlicher Funktionen ist fraglich, da der ursprüngliche Zweck der Anwendung darin besteht, ein extrem leichtgewichtiges (in C++ geschriebenes) Applet zu sein, und die Ausführung weniger Funktionen sollte die Anwendung nicht zu sehr aufblähen.

## Achtung
**Da der Autor diese Win32-Anwendung nicht *digital signiert* hat, besteht eine gute Chance, dass die Anwendung, wenn sie mit Microsoft Edge heruntergeladen oder unter Windows ausgeführt wird, mit einem Smart Screen blockiert wird. Da es sich jedoch um ein Open-Source-Programm handelt, ist es unwahrscheinlich, dass es schädliche Funktionen hat, also können Sie es gerne verwenden.**

Übersetztung ende

## Bauen vom Quellcode

+ Insatlliere Visual Studio (Hier würde 2022 verwendet bzw. 17)
+ Öffne die Datei 'KeyboardLocker.sln'
+ Installiere alle benötigten bahängigkeiten
+ (Optional) mache deine Anpassungen
+ Starte den Build-Prozess
