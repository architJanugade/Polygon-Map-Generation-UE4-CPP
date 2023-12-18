# Polygon-Map-Generation-UE4-CPP



**Created for Unreal Engine 4.21:** 
_**I actually finished this project 2 years ago but I didn't upload it on GitHub. So here it is.**_



![50578306-17d8b880-0ded-11e9-8b8d-b7641fcd7479](https://github.com/architJanugade/Polygon-Map-Generation-UE4-CPP/assets/48153450/ba563645-7f01-49e0-a09d-e06e8feb980b)

This is a port of the JavaScript code of Red Blob Games' Polygonal Map Generation for Games.

This port is written in C++ and designed to work in Unreal Engine 4 using the Unreal Engine 4 "Plugin" system. This port works fully with games written in C++ as well as games that use Unreal Engine 4's "Blueprint" system.

It supports Unreal Engine version 4.21.x; You can probably use it for earlier/later versions of the Unreal Engine, but you may have to make slight modifications.

![50556436-f0b7a500-0c8d-11e9-92fe-0da8a22dbee8](https://github.com/architJanugade/Polygon-Map-Generation-UE4-CPP/assets/48153450/7cdd5296-085c-4fd7-81cf-430a74110706)
![50556433-f0b7a500-0c8d-11e9-8636-21dc94e46699](https://github.com/architJanugade/Polygon-Map-Generation-UE4-CPP/assets/48153450/999242fd-d71b-4a44-bf3c-839cf5da1156)

Installation
Access through Blueprint only:
If you only want to access everything through Blueprint, you can just clone this project into your <Project Root>/Plugins folder, where <Project Root> is where the .uplugin file is kept. You may have to create the Plugins folder if you haven't made it already. From there, you should be able to drag the pre-made Blueprints into your scene, create new custom Blueprints, or do whatever else you need.

Access through C++ and Blueprints:
Make a Plugins folder at your project root (where the .uproject file is), if you haven't already. Then, clone this project into a subfolder in your Plugins directory. After that, open up your project's .uproject file in Notepad (or a similar text editor), and change the "AdditionalDependencies" and "Plugins" sections to look like this:

```
"Modules": [
		{
			"Name": "YourProjectName",
			"Type": "Runtime",
			"LoadingPhase": "Default",
			"AdditionalDependencies": [
				<OTHER DEPENDENCIES GO HERE>
				"PolygonalMapGenerator"
			]
		}
	],
	"Plugins": [
		<OTHER PLUGINS GO HERE>
		{
			"Name": "PolygonalMapGenerator",
			"Enabled": true
		}
	]
```

If you don't have a "Modules" section, then that usually means that your project isn't set up for C++ yet. First, set your project up to handle C++ code, then you should see the "Modules" section. It's okay if you don't see a "Plugins" section, however -- just add one in there.

In the past, I have gotten linker errors by not listing this in the .uproject file when trying to package a project. People have said you don't need to do it nowadays, so you might be able to skip this step -- even so, I'm listing it here in case any problems arise.

Go into your source code folder, and you'll see a `.build.cs file. Open it up. Under either "PrivateDependencyModuleNames" or "PublicDependencyModuleNames" add a new entry called "PolygonalMapGenerator".
This lets Unreal's Blueprint reflection system "see" your plugin and know to compile it before it compiles the rest of your code, so that you don't get weird linker errors when using things from the plugin.

Open up your project in Unreal. If you get a prompt asking for an Unreal Engine version, you probably missed a comma somewhere in your .uproject file -- make sure all the commas and syntax are correct and try again. If Unreal does start to load, you might be told that your project is out of date, and the editor will ask if you want to rebuild your project. Go ahead and say yes so the plugin can be installed properly (keeping in mind that it might take a while to rebuild).

Open up the Plugins menu, scroll down to the bottom, and ensure that the "PolygonalMapGenerator" plugin is enabled.

Once you have the project set up, you should be able to see it in the sidebar of the Content Browser; simply scroll down to "Polygonal Map Generator." You'll see 2 folders -- "Content" and "C++ Classes." If you don't see it in the Unreal Engine editor, make sure to turn on "Show Plugin Content" in the view options in the bottom-right corner.

The "C++ Classes" folder contains, well, the C++ classes. You can right-click on them to create a new Blueprint or C++ class from the classes listed in that folder, or you can just do it the old-fashioned way, like you would inherit from Unreal's Actor class.

The "Content" folder contains a bunch of content that can help you when making your own version of the plugin. If you wanted to, you could delete these files, but they give examples on how to set up a map generator and what the different classes in the plugin actually do.


**Credits:**
The original code was released under the Apache 2.0 license; this C++ port of the code is also released under the Apache 2.0 license. Again, this was based on the mapgen2 repository.

Also included in this code is a port of the DualMesh library; DualMesh is also licensed under Apache 2.0.

Poisson Disc Sampling is created using code from the Random Distribution Plugin and used under the Apache 2.0 license.

Delaunay Triangulation is created using the MIT-licensed Delaunator and made accessible through a number of Unreal helper functions. Something that's fairly annoying: Delaunay Triangulation is built into the engine, but is only accessible from the Unreal Editor. The data structures aren't exposed to other modules or Blueprint, so you can't use it without linker errors when shipping your game. The Unreal Engine code has a different license, so a third-party library has to be used.
