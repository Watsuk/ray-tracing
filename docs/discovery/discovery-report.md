# Discovery report

## Problem statement

A renowned film studio needs a reliable, maintainable, and fully open-source C++ ray tracer capable of distributed headless rendering, because their previous AI-generated tools failed unpredictably and commercial licenses cost millions while lacking extensibility.

## Client interview summary

### Maintainability and Past Failures

**Need:** A predictable, debuggable rendering pipeline.
> **Q (Class):** "Can you walk us through the last time your rendering pipeline failed? What exactly happened?"
> **A:** "6 months ago, on a big project, we had black artifacts and rendering time doubled. Nobody could figure out why. We had to buy a commercial project and were 3 weeks late."

**Need:** Highly maintainable code (Clean Code / SOLID).
> **Q (Class):** "When a render fails or produces an artifact, what is your acceptable time limit to diagnose and fix it?"
> **A:** "Reliable image, figure out the anomaly in a day."

**Need:** Maintainability over disposable code.
> **Q (Class):** "What are your primary long-term goals for this new software?"
> **A:** "In-house software, long term, maintainable."

**Need:** Full ownership of the IP.
> **Q (Class):** "What was the legal or business issue with using external generated code or commercial engines?"
> **A:** "Property of the code problem."

**My conclusion:** The transition to C++ is strictly about control and predictability. AI-generated code failed because it was a black box. The architecture must prioritize clean, SOLID OOP design over "clever" but unreadable optimizations, so any engineer can trace a bug in under 24 hours.

### Scale and Performance Requirements

**Need:** Fast feedback for artists during the workday.
> **Q (Class):** "What do you consider a reasonable render time for a single frame?"
> **A:** "Reasonable render time = not sure, for the team to work correctly, very quickly."

**Need:** A real-time or low-latency preview mode.
> **Q (Class):** "What is the hardware and quality expectation for artists working locally on their workstations?"
> **A:** "For design, desktop machines, to work and visualize. Smaller image is OK, fast image."

**Need:** Headless execution optimized for CPU throughput.
> **Q (Class):** "How does the final production rendering environment differ from the artists' desktops?"
> **A:** "Production render: large machines, large specs. No graphics (GUI), full CPU, high quality."

**Need:** Distributed rendering capability across a specific cluster size.
> **Q (Class):** "How many machines are currently available in your production render farm?"
> **A:** "100 machines."

**Need:** Performance capable of hitting a strict mathematical target (~1h06m per frame).
> **Q (Class):** "Can you break down the scale of a full project and the time allocated for the final render phase?"
> **A:** "After the creative side, we have 2 months for rendering, 10 prerenders per image. It's a 90-minute film in HD 24fps, full animation, Toy Story style."

**My conclusion:** We can now calculate the exact performance target. 90 minutes at 24fps = 129,600 final frames. 100 machines working for 2 months (~60 days) means the farm processes ~2,160 frames a day, or ~21.6 frames per machine per day. Therefore, a single final high-quality HD frame must render in under 1 hour and 6 minutes on a production node. The architecture must strictly separate the core logic from the GUI to allow headless farm execution.

### Ecosystem and Pipeline

**Need:** An extensible architecture starting with a simple MVP.
> **Q (Class):** "What specific geometric shapes or features must the ray tracer support right now, and how will this evolve?"
> **A:** "Requirements change every project, the tool must accept all. Render spheres and planes for now."

**Need:** Interoperability with existing 3D modeling tools.
> **Q (Class):** "What software are your 3D artists using today to design the scenes?"
> **A:** "For rendering design today, we use Maya."

**Need:** A parser for external scene files.
> **Q (Class):** "How does a scene travel from the 3D artist to the actual rendering engine?"
> **A:** "Design is in third-party software. The file is sent into the raytracing software."

**Need:** Customization that commercial tools don't offer.
> **Q (Class):** "If Maya has its own renderer, why do you need a custom solution?"
> **A:** "Features that Maya doesn't have = adding our own features."

**Need:** A modular architecture accessible to external developers.
> **Q (Class):** "Who else besides your internal team will be interacting with this software?"
> **A:** "Rendering relies on partners, they will use the software."

**Need:** Developer experience (DX) and technical writing.
> **Q (Class):** "Since partners will be using it, what level of onboarding materials do you require?"
> **A:** "User guide, documentation."

**My conclusion:** The project requires a robust file parser to decouple scene creation from rendering. The core must be highly modular (e.g., using interfaces for shapes and materials) so partners can inject custom features without modifying the engine's core loop.

### Business Constraints

**Need:** Strict adherence to the delivery schedule.
> **Q (Class):** "What is the strict deadline for delivering this new rendering engine?"
> **A:** "Deadline is January 5th."

**Need:** Cost-efficiency and feature control.
> **Q (Class):** "Why not just buy an off-the-shelf commercial ray tracer?"
> **A:** "Comparisons = expensive, we lose money on the project, they don't satisfy all the needs, and we have to sacrifice features."

**Need:** Drastic cost reduction compared to legacy solutions.
> **Q (Class):** "How much were you spending previously on commercial rendering licenses?"
> **A:** "2M dollars for the license before."

**Need:** Zero proprietary licensing lock-in.
> **Q (Class):** "Under what kind of license or distribution model should this project be released?"
> **A:** "Full open source."

**Need:** Strict budget management.
> **Q (Class):** "What is the hard budget cap for developing this new ray tracer?"
> **A:** "500,000€ max on the project."

**My conclusion:** Building in-house avoids proprietary lock-in and IP issues. The budget and deadline mean we cannot build everything from scratch—we must stick strictly to the MVP (spheres, planes, basic CLI) and rely on the open-source community for future scaling.

### Open questions

- What exact scene file format will Maya export for the ray tracer to read?
- What are the exact hardware specifications (RAM, CPU cores, clock speed) of the 100 production machines?
- What operating systems are running on the artists' desktops versus the headless render nodes?

## State of the art

| Solution | Maker | Licence | Pricing (Nov 2026) | Capabilities | Sources |
|---|---|---|---|---|---|
| RenderMan | Pixar | Proprietary | ~$595/licence | Industry standard, advanced path tracing, USD integration | renderman.pixar.com |
| Arnold | Autodesk | Proprietary | ~$400/year | Highly optimized for VFX, seamless Maya integration | autodesk.com/products/arnold |
| V-Ray | Chaos | Proprietary | ~$470/year | Excellent architectural rendering, fast global illumination | chaos.com/vray |
| Cycles | Blender | GNU GPL | Free | Physically based path tracer, GPU accelerated | blender.org |

The market is dominated by expensive, proprietary solutions. At $595 per license, equipping 100 farm nodes and dozens of artists costs hundreds of thousands of dollars annually, which violates the client's business model (as proven by their past $2M expenditure). While open-source alternatives like Cycles exist, the client requires a custom, highly maintainable solution optimized specifically for their internal pipeline and partner ecosystem, mitigating the risks of proprietary lock-in and the operational hazards of unmaintainable AI-generated legacy code.

## What is ray tracing?

Ray tracing is a rendering technique that simulates the physical behavior of light by tracing the paths of light rays backwards from the camera (the viewer's eye) into a 3D scene. As these rays intersect with digital objects, the algorithm calculates color and illumination based on physical properties such as reflection, refraction, absorption, and shadows. By recursively tracking how rays bounce between surfaces before reaching light sources, it produces highly photorealistic images, albeit at a high computational cost compared to traditional rasterization.

**Sources:**
- Started from: *Ray Tracing in One Weekend* by Peter Shirley (https://raytracing.github.io/)
- Reference: *Physically Based Rendering: From Theory to Implementation* (https://pbr-book.org/)

## What is C++?

### Programming paradigms
Unlike Go or TypeScript, C++ is a compiled language that supports multiple paradigms. It allows procedural programming, object-oriented programming (OOP), and generic programming (via templates and metaprogramming). It provides extreme flexibility, allowing developers to write high-level abstractions while maintaining low-level control over system resources.

### What to watch out for
C++ does not have a garbage collector. Memory must be managed manually or through smart pointers (RAII). The primary risks are memory leaks, segmentation faults, and undefined behavior resulting from dangling pointers or out-of-bounds access. Furthermore, AI-generated C++ code can easily introduce subtle memory bugs or inefficient abstractions that compile successfully but fail unpredictably at runtime.

### Shaping the domain model
C++ allows for zero-cost abstractions, meaning the domain model can be highly structured without sacrificing performance. OOP (encapsulation, polymorphism) can be used to model varying scene entities like materials and shapes, while data-oriented design (using structs and contiguous arrays) can be leveraged for mathematical constructs (vectors, rays) to maximize CPU cache locality, which is critical for the millions of calculations required in ray tracing.

**Sources:**
- Started from: LearnCpp.com (https://www.learncpp.com/)
- Reference: cppreference.com (https://en.cppreference.com/)
