/*
 *  Shaders - Vulkan style
 *
 *  Adapted from vulkan-tutorial.com
 *
 *  Key bindings:
 *  p/P        Toggle between orthogonal & perspective projection
 *  m/M        Stop/start light movement
 *  -/+        Move light up/down
 *  [/]        Move light in orbit
 *  arrows     Change view angle
 *  ESC        Exit
 *
 */

//  KILLER FACT:  Most structs have LOTS of fields you may not care about,
//    but must be initialized.  Use the C99 syntax
//       var = {.field=val,.field=val,...,.field=val};
//    to make sure that the rest of the struct is properly initialized.
//    Unspecified fields are initialized to zeroes.

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include "mat4.h"

//  cos and sin in degrees
#define Cos(th) cos(3.14159265/180*(th))
#define Sin(th) sin(3.14159265/180*(th))

#define NFRAMES 2                                           // Frames in flight
int                      move=1;                            // Light movement
int                      th=0,ph=0,zh=0;                    // View angles
int                      proj=1;                            // Projection type
float                    fov=55;                            // Field of view
float                    Ylight=2;                          // Light elevation
float                    dim=3.0;                           // Size of world
GLFWwindow*              window;                            // GLFW window
VkInstance               instance;                          // Vulkan instance
VkSurfaceKHR             surface;                           // Drawing surface
VkDevice                 device;                            // Selected device
VkPhysicalDevice         physicalDevice;                    // Physical device
VkQueue                  graphicsQueue;                     // Graphics queue
VkQueue                  presentQueue;                      // Present queue
uint32_t                 swapCount;                         // Swap count
VkSwapchainKHR           swapChain;                         // Swap chain
VkExtent2D               swapChainExtent;                   // Swap chain extent
VkImageView*             swapChainImageViews;               // Swap chain image views
VkFramebuffer*           swapChainFramebuffers;             // Swap chain framebuffers
VkFormat                 swapChainImageFormat;              // Swapchain image format
VkFormat                 depthFormat;                       // Z-buffer format
VkImage                  depthImage;                        // Z-buffer image
VkDeviceMemory           depthImageMemory;                  // Z-buffer image memory
VkImageView              depthImageView;                    // Z-buffer image view
VkRenderPass             renderPass;                        // Render pass
VkDescriptorSetLayout    descriptorSetLayout;               // Descriptor set layout
VkPipelineLayout         pipelineLayout;                    // Pipeline layout
VkPipeline               graphicsPipeline;                  // Graphics pipeline
VkCommandPool            commandPool;                       // Command pool
uint32_t                 currentFrame=0;                    // Current frame
VkCommandBuffer          commandBuffers[NFRAMES];           // Command buffer
VkSemaphore              imageAvailableSemaphores[NFRAMES]; // Image available semaphore
VkSemaphore              renderFinishedSemaphores[NFRAMES]; // Render finished sempahore
VkFence                  inFlightFences[NFRAMES];           // In flight fence
int                      framebufferResized=0;              // Resize frame
uint32_t                 formatCount=0;                     // Number for formats
VkSurfaceFormatKHR*      formats=NULL;                      // Surface formats
uint32_t                 presentModeCount=0;                // Number of presentation modes
VkPresentModeKHR*        presentModes=NULL;                 // Presentation modes
VkSurfaceCapabilitiesKHR capabilities;                      // Physical device capabilities
uint32_t                 graphicsFamily=0;                  // Graphics family
uint32_t                 presentFamily=0;                   // Presentation family
VkBuffer                 vertexBuffer;                      // Vertex buffer
VkDeviceMemory           vertexBufferMemory;                // Vertex buffer memory
VkBuffer                 uniformBuffers[NFRAMES];           // Uniform buffers
VkDeviceMemory           uniformBuffersMemory[NFRAMES];     // Uniform buffer memory
void*                    uniformBuffersMapped[NFRAMES];     // Mapping for uniform buffer
VkDescriptorPool         descriptorPool;                    // Descriptor pool
VkDescriptorSet          descriptorSets[NFRAMES];           // Descriptor sets
VkImage                  textureImage;                      // Texture image
VkDeviceMemory           textureImageMemory;                // Texture image memory
VkImageView              textureImageView;                  // Texture image view
VkSampler                textureSampler;                    // Texture sampler

//  Define cube
typedef struct {float x,y;}     vec2;
typedef struct {float x,y,z;}   vec3;
typedef struct {float x,y,z,w;} vec4;
typedef struct {vec3 xyz,nml,rgb;vec2 st;} Vertex;
typedef struct
{
   float model[16],view[16],proj[16],norm[16]; // Transformation matrices
   vec4  pos,Ca,Cd,Cs;                         // Light properties
   vec4  Ks;                                   // Material properties
   float Ns;                                   //
} UniformBufferObject;
const Vertex vertices[] =
{
   //  Front
   {{-1,-1,+1}, {0,0,+1}, {1,0,0}, {0,0}},
   {{+1,-1,+1}, {0,0,+1}, {1,0,0}, {1,0}},
   {{+1,+1,+1}, {0,0,+1}, {1,0,0}, {1,1}},
   {{+1,+1,+1}, {0,0,+1}, {1,0,0}, {1,1}},
   {{-1,+1,+1}, {0,0,+1}, {1,0,0}, {0,1}},
   {{-1,-1,+1}, {0,0,+1}, {1,0,0}, {0,0}},
   //  Back              
   {{+1,-1,-1}, {0,0,-1}, {0,0,1}, {0,0}},
   {{-1,-1,-1}, {0,0,-1}, {0,0,1}, {1,0}},
   {{-1,+1,-1}, {0,0,-1}, {0,0,1}, {1,1}},
   {{-1,+1,-1}, {0,0,-1}, {0,0,1}, {1,1}},
   {{+1,+1,-1}, {0,0,-1}, {0,0,1}, {0,1}},
   {{+1,-1,-1}, {0,0,-1}, {0,0,1}, {0,0}},
   //  Right             
   {{+1,-1,+1}, {+1,0,0}, {1,1,0}, {0,0}},
   {{+1,-1,-1}, {+1,0,0}, {1,1,0}, {1,0}},
   {{+1,+1,-1}, {+1,0,0}, {1,1,0}, {1,1}},
   {{+1,+1,-1}, {+1,0,0}, {1,1,0}, {1,1}},
   {{+1,+1,+1}, {+1,0,0}, {1,1,0}, {0,1}},
   {{+1,-1,+1}, {+1,0,0}, {1,1,0}, {0,0}},
   //  Left              
   {{-1,-1,-1}, {-1,0,0}, {0,1,0}, {0,0}},
   {{-1,-1,+1}, {-1,0,0}, {0,1,0}, {1,0}},
   {{-1,+1,+1}, {-1,0,0}, {0,1,0}, {1,1}},
   {{-1,+1,+1}, {-1,0,0}, {0,1,0}, {1,1}},
   {{-1,+1,-1}, {-1,0,0}, {0,1,0}, {0,1}},
   {{-1,-1,-1}, {-1,0,0}, {0,1,0}, {0,0}},
   //  Top               
   {{-1,+1,+1}, {0,+1,0}, {0,1,1}, {0,0}},
   {{+1,+1,+1}, {0,+1,0}, {0,1,1}, {1,0}},
   {{+1,+1,-1}, {0,+1,0}, {0,1,1}, {1,1}},
   {{+1,+1,-1}, {0,+1,0}, {0,1,1}, {1,1}},
   {{-1,+1,-1}, {0,+1,0}, {0,1,1}, {0,1}},
   {{-1,+1,+1}, {0,+1,0}, {0,1,1}, {0,0}},
   //  Bottom            
   {{-1,-1,-1}, {0,-1,0}, {1,0,1}, {0,0}},
   {{+1,-1,-1}, {0,-1,0}, {1,0,1}, {1,0}},
   {{+1,-1,+1}, {0,-1,0}, {1,0,1}, {1,1}},
   {{+1,-1,+1}, {0,-1,0}, {1,0,1}, {1,1}},
   {{-1,-1,+1}, {0,-1,0}, {1,0,1}, {0,1}},
   {{-1,-1,-1}, {0,-1,0}, {1,0,1}, {0,0}},
};

//
//  Print message to stderr and exit
//
void Fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

const char* ErrString(VkResult err)
{
   switch (err)
   {
   case VK_SUCCESS: return "VK_SUCCESS";
   case VK_NOT_READY: return "VK_NOT_READY";
   case VK_TIMEOUT: return "VK_TIMEOUT";
   case VK_EVENT_SET: return "VK_EVENT_SET";
   case VK_EVENT_RESET: return "VK_EVENT_RESET";
   case VK_INCOMPLETE: return "VK_INCOMPLETE";
   case VK_ERROR_OUT_OF_HOST_MEMORY: return "VK_ERROR_OUT_OF_HOST_MEMORY";
   case VK_ERROR_OUT_OF_DEVICE_MEMORY: return "VK_ERROR_OUT_OF_DEVICE_MEMORY";
   case VK_ERROR_INITIALIZATION_FAILED: return "VK_ERROR_INITIALIZATION_FAILED";
   case VK_ERROR_DEVICE_LOST: return "VK_ERROR_DEVICE_LOST";
   case VK_ERROR_MEMORY_MAP_FAILED: return "VK_ERROR_MEMORY_MAP_FAILED";
   case VK_ERROR_LAYER_NOT_PRESENT: return "VK_ERROR_LAYER_NOT_PRESENT";
   case VK_ERROR_EXTENSION_NOT_PRESENT: return "VK_ERROR_EXTENSION_NOT_PRESENT";
   case VK_ERROR_FEATURE_NOT_PRESENT: return "VK_ERROR_FEATURE_NOT_PRESENT";
   case VK_ERROR_INCOMPATIBLE_DRIVER: return "VK_ERROR_INCOMPATIBLE_DRIVER";
   case VK_ERROR_TOO_MANY_OBJECTS: return "VK_ERROR_TOO_MANY_OBJECTS";
   case VK_ERROR_FORMAT_NOT_SUPPORTED: return "VK_ERROR_FORMAT_NOT_SUPPORTED";
   case VK_ERROR_FRAGMENTED_POOL: return "VK_ERROR_FRAGMENTED_POOL";
   case VK_ERROR_UNKNOWN: return "VK_ERROR_UNKNOWN";
   case VK_ERROR_OUT_OF_POOL_MEMORY: return "VK_ERROR_OUT_OF_POOL_MEMORY";
   case VK_ERROR_INVALID_EXTERNAL_HANDLE: return "VK_ERROR_INVALID_EXTERNAL_HANDLE";
   case VK_ERROR_FRAGMENTATION: return "VK_ERROR_FRAGMENTATION";
   case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: return "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS";
   case VK_ERROR_SURFACE_LOST_KHR: return "VK_ERROR_SURFACE_LOST_KHR";
   case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: return "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
   case VK_SUBOPTIMAL_KHR: return "VK_SUBOPTIMAL_KHR";
   case VK_ERROR_OUT_OF_DATE_KHR: return "VK_ERROR_OUT_OF_DATE_KHR";
   case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: return "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
   case VK_ERROR_VALIDATION_FAILED_EXT: return "VK_ERROR_VALIDATION_FAILED_EXT";
   case VK_ERROR_INVALID_SHADER_NV: return "VK_ERROR_INVALID_SHADER_NV";
   case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: return "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT";
   case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: return "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT";
#ifdef VK_API_VERSION_1_3_0
   case VK_PIPELINE_COMPILE_REQUIRED: return "VK_PIPELINE_COMPILE_REQUIRED";
   case VK_ERROR_NOT_PERMITTED_KHR: return "VK_ERROR_NOT_PERMITTED_KHR";
   case VK_THREAD_IDLE_KHR: return "VK_THREAD_IDLE_KHR";
   case VK_THREAD_DONE_KHR: return "VK_THREAD_DONE_KHR";
   case VK_OPERATION_DEFERRED_KHR: return "VK_OPERATION_DEFERRED_KHR";
   case VK_OPERATION_NOT_DEFERRED_KHR: return "VK_OPERATION_NOT_DEFERRED_KHR";
#endif
   default: return "Unknown VkResult";
   }
}

//
//  Find index if memory type
//
uint32_t findMemoryType(uint32_t typeFilter,VkMemoryPropertyFlags properties)
{
   VkPhysicalDeviceMemoryProperties memProperties;
   vkGetPhysicalDeviceMemoryProperties(physicalDevice,&memProperties);
   for (int k=0;k<memProperties.memoryTypeCount;k++)
      if ((typeFilter&(1<<k)) && (memProperties.memoryTypes[k].propertyFlags&properties)==properties)
         return k;
   Fatal("Failed to find suitable memory type\n");
   return 0;
}

//
//  Create a buffer and allocate memory
//
void CreateBuffer(VkDeviceSize size,VkBufferUsageFlags usage,VkMemoryPropertyFlags properties,VkBuffer* buffer,VkDeviceMemory* bufferMemory)
{
   //  Create buffer
   VkBufferCreateInfo bufferInfo =
   {
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
      .size  = size,
      .usage = usage,
      .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
   };
   int ios = vkCreateBuffer(device,&bufferInfo,NULL,buffer);
   if (ios) Fatal("Failed to create buffer: %s\n",ErrString(ios));

   //  Get memory requirements for buffer
   VkMemoryRequirements memRequirements;
   vkGetBufferMemoryRequirements(device,*buffer,&memRequirements);

   //  Allocate memory for buffer
   VkMemoryAllocateInfo allocInfo =
   {
      .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
      .allocationSize = memRequirements.size,
      .memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties),
   };
   if (vkAllocateMemory(device,&allocInfo,NULL,bufferMemory))
      Fatal("Failed to allocate buffer memory\n");

   //  Bind buffer and memory
   vkBindBufferMemory(device,*buffer,*bufferMemory,0);
}

//
//  Copy buffer
//
void CopyBuffer(VkBuffer srcBuffer,VkBuffer dstBuffer,VkDeviceSize size)
{
   //  Create command buffer
   VkCommandBufferAllocateInfo allocInfo =
   {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandPool = commandPool,
      .commandBufferCount = 1,
   };
   VkCommandBuffer commandBuffer;
   vkAllocateCommandBuffers(device,&allocInfo,&commandBuffer);

   //  Set up one time copy
   VkCommandBufferBeginInfo beginInfo =
   {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
      .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
   };

   //  Set copy command
   vkBeginCommandBuffer(commandBuffer,&beginInfo);
   VkBufferCopy copyRegion = {.size=size};
   vkCmdCopyBuffer(commandBuffer,srcBuffer,dstBuffer,1,&copyRegion);
   vkEndCommandBuffer(commandBuffer);

   //  Perform copy
   VkSubmitInfo submitInfo =
   {
      .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
      .commandBufferCount = 1,
      .pCommandBuffers = &commandBuffer,
   };
   vkQueueSubmit(graphicsQueue,1,&submitInfo,VK_NULL_HANDLE);
   vkQueueWaitIdle(graphicsQueue);

   //  Free up command buffer
   vkFreeCommandBuffers(device,commandPool,1,&commandBuffer);
}

//
//  Create vertex buffer
//
void CreateVertexBuffer()
{
   VkDeviceSize bufferSize = sizeof(vertices);

   VkBuffer stagingBuffer;
   VkDeviceMemory stagingBufferMemory;
   CreateBuffer(bufferSize,VK_BUFFER_USAGE_TRANSFER_SRC_BIT,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,&stagingBuffer,&stagingBufferMemory);

   void* data;
   vkMapMemory(device,stagingBufferMemory,0,bufferSize,0,&data);
   memcpy(data,vertices,bufferSize);
   vkUnmapMemory(device,stagingBufferMemory);

   CreateBuffer(bufferSize,VK_BUFFER_USAGE_TRANSFER_DST_BIT|VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,&vertexBuffer,&vertexBufferMemory);

   CopyBuffer(stagingBuffer,vertexBuffer,bufferSize);

   vkDestroyBuffer(device,stagingBuffer,NULL);
   vkFreeMemory(device,stagingBufferMemory,NULL);
}

//
//  Create shader module
//
VkShaderModule CreateShaderModule(const char* file)
{
   //  Open file
   FILE* f = fopen(file,"rb");
   if (!f) Fatal("Cannot open shader file %s\n",file);
   //  Seek to end to determine size, then rewind
   fseek(f,0,SEEK_END);
   int n = ftell(f);
   rewind(f);
   //  Allocate memory for the whole file
   uint32_t* code = (uint32_t*)malloc(n);
   if (!code) Fatal("Failed to malloc %d bytes for shader file %s\n",n,file);
   //  Snarf and close the file
   if (fread(code,n,1,f)!=1) Fatal("Cannot read %d bytes from shader file %s\n",n,file);
   fclose(f);
   //  Fill in shader struct
   VkShaderModuleCreateInfo shaderInfo =
   {
      .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
      .codeSize = n,
      .pCode    = code,
   };
   //  Create shader
   VkShaderModule shaderModule;
   if (vkCreateShaderModule(device,&shaderInfo,NULL,&shaderModule))
      Fatal("Failed to create shader module\n");
   //  Free code and return
   free(code);
   return shaderModule;
}

//
//  Create image and allocate memory
//
void CreateImage(uint32_t width, uint32_t height,VkFormat format,VkImageTiling tiling,VkImageUsageFlags usage,VkMemoryPropertyFlags properties,VkImage* image,VkDeviceMemory* imageMemory)
{
   const VkImageCreateInfo imageInfo =
   {
      .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
      .imageType = VK_IMAGE_TYPE_2D,
      .extent.width = width,
      .extent.height = height,
      .extent.depth = 1,
      .mipLevels = 1,
      .arrayLayers = 1,
      .format = format,
      .tiling = tiling,
      .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
      .usage = usage,
      .samples = VK_SAMPLE_COUNT_1_BIT,
      .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
   };
   int ios = vkCreateImage(device,&imageInfo,NULL,image);
   if (ios) Fatal("Failed to create %dx%d image: %s\n",width,height,ErrString(ios));

   //  Allocate memory for image
   VkMemoryRequirements memRequirements;
   vkGetImageMemoryRequirements(device,*image,&memRequirements);
   VkMemoryAllocateInfo allocInfo =
   {
      .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
      .allocationSize = memRequirements.size,
      .memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties),
   };
   if (vkAllocateMemory(device,&allocInfo,NULL,imageMemory))
      Fatal("Failed to allocate image memory\n");

   //  Bind memory to image
   vkBindImageMemory(device,*image,*imageMemory,0);
}

//
//  Create image view
//
VkImageView CreateImageView(VkImage image,VkFormat format,VkImageAspectFlags aspectFlags)
{
   VkImageViewCreateInfo viewInfo =
   {
      .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
      .image = image,
      .viewType = VK_IMAGE_VIEW_TYPE_2D,
      .format = format,
      .subresourceRange.aspectMask = aspectFlags,
      .subresourceRange.baseMipLevel = 0,
      .subresourceRange.levelCount = 1,
      .subresourceRange.baseArrayLayer = 0,
      .subresourceRange.layerCount = 1,
   };
   VkImageView imageView;
   if (vkCreateImageView(device,&viewInfo,NULL,&imageView))
      Fatal("Failed to create texture image view\n");
   return imageView;
}

//
//  Destroy swapchain
//
void DestroySwapChain()
{
   vkDestroyImageView(device,depthImageView,NULL);
   vkDestroyImage(device,depthImage,NULL);
   vkFreeMemory(device,depthImageMemory,NULL);
   for (int k=0;k<swapCount;k++)
      vkDestroyFramebuffer(device,swapChainFramebuffers[k],NULL);
   free(swapChainFramebuffers);
   for (int k=0;k<swapCount;k++)
      vkDestroyImageView(device,swapChainImageViews[k],NULL);
   free(swapChainImageViews);
   vkDestroySwapchainKHR(device,swapChain,NULL);
}

//
//  Create swapchain
//
void CreateSwapChain(int init)
{
   //  Destroy old swapchain if it exists
   if (!init)
   {
      //  If minimized wait here
      int width=0,height=0;
      while (width==0 || height==0)
      {
         glfwGetFramebufferSize(window,&width,&height);
         glfwWaitEvents();
      }
      //  Make sure everything is processed
      vkDeviceWaitIdle(device);
      //  Delete old swapchain
      DestroySwapChain();
   }

   //  Set surface format
   VkSurfaceFormatKHR surfaceFormat = formats[0];
   for (int k=0;k<formatCount;k++)
      if (formats[k].format==VK_FORMAT_B8G8R8A8_SRGB &&
          formats[k].colorSpace==VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
         surfaceFormat = formats[k];

   //  Set present mode
   VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;
   for (int k=0;k<presentModeCount;k++)
      if (presentModes[k]==VK_PRESENT_MODE_MAILBOX_KHR)
         presentMode = presentModes[k];

   //  Set  extent
   VkExtent2D extent;
   vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice,surface,&capabilities);
   if (capabilities.currentExtent.width != UINT32_MAX)
   {
      extent = capabilities.currentExtent;
   }
   else
   {
      int width, height;
      glfwGetFramebufferSize(window,&width,&height);
      if (width<capabilities.minImageExtent.width) width = capabilities.minImageExtent.width;
      if (width>capabilities.maxImageExtent.width) width = capabilities.maxImageExtent.width;
      if (height<capabilities.minImageExtent.height) height = capabilities.minImageExtent.height;
      if (height>capabilities.maxImageExtent.height) height = capabilities.maxImageExtent.height;
      extent.width  = width;
      extent.height = height;
   }

   //  Set number of images
   uint32_t imageCount = capabilities.minImageCount+1;
   if (capabilities.maxImageCount>0 && imageCount>capabilities.maxImageCount)
      imageCount = capabilities.maxImageCount;

   //  Create swap chain
   VkSwapchainCreateInfoKHR chainInfo =
   {
      .sType            = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
      .surface          = surface,
      .minImageCount    = imageCount,
      .imageFormat      = surfaceFormat.format,
      .imageColorSpace  = surfaceFormat.colorSpace,
      .imageExtent      = extent,
      .imageArrayLayers = 1,
      .imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
   };
   uint32_t queueFamilyIndices[] = {graphicsFamily,presentFamily};
   if (graphicsFamily != presentFamily)
   {
      chainInfo.imageSharingMode      = VK_SHARING_MODE_CONCURRENT;
      chainInfo.queueFamilyIndexCount = 2;
      chainInfo.pQueueFamilyIndices   = queueFamilyIndices;
   }
   else
      chainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
   chainInfo.preTransform   = capabilities.currentTransform;
   chainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
   chainInfo.presentMode    = presentMode;
   chainInfo.clipped        = VK_TRUE;
   chainInfo.oldSwapchain   = VK_NULL_HANDLE;
   if (vkCreateSwapchainKHR(device,&chainInfo,NULL,&swapChain))
      Fatal("Failed to create swap chain\n");

   //  Create swap chain images
   vkGetSwapchainImagesKHR(device,swapChain,&swapCount,NULL);
   VkImage* swapChainImages = (VkImage*)malloc(swapCount*sizeof(VkImage));
   if (!swapChainImages) Fatal("Failed to malloc %d VkImage\n",swapCount);
   vkGetSwapchainImagesKHR(device,swapChain,&swapCount,swapChainImages);
   swapChainImageFormat = surfaceFormat.format;
   swapChainExtent = extent;

   //  Create image views
   swapChainImageViews = (VkImageView*)malloc(swapCount*sizeof(VkImageView));
   for (int i=0;i<swapCount;i++)
      swapChainImageViews[i] = CreateImageView(swapChainImages[i],swapChainImageFormat,VK_IMAGE_ASPECT_COLOR_BIT);

   //
   //  Create render pass if it does not exist
   //
   if (init)
   {
      //  Color buffer attachment
      VkAttachmentDescription colorAttachment =
      {
         .format         = swapChainImageFormat,
         .samples        = VK_SAMPLE_COUNT_1_BIT,
         .loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR,
         .storeOp        = VK_ATTACHMENT_STORE_OP_STORE,
         .stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
         .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
         .initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED,
         .finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
      };
      //  Find optimal depth format
      VkFormatFeatureFlags features = VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;
      depthFormat = VK_FORMAT_UNDEFINED;
      VkFormat formats[] = {VK_FORMAT_D24_UNORM_S8_UINT,VK_FORMAT_D32_SFLOAT_S8_UINT,VK_FORMAT_D32_SFLOAT};
      for (int k=0;k<sizeof(formats)/sizeof(VkFormat);k++)
      {
         VkFormatProperties props;
         vkGetPhysicalDeviceFormatProperties(physicalDevice,formats[k],&props);
         if ((props.optimalTilingFeatures & features) == features)
            depthFormat = formats[k];
      }
      if (depthFormat==VK_FORMAT_UNDEFINED)
         Fatal("Failed to find supported depth format\n");
      //  Depth buffer attachment
      VkAttachmentDescription depthAttachment =
      {
         .format = depthFormat,
         .samples = VK_SAMPLE_COUNT_1_BIT,
         .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
         .storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
         .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
         .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
         .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
         .finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
      };
      VkAttachmentReference colorAttachmentRef = {.attachment=0,.layout=VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
      VkAttachmentReference depthAttachmentRef = {.attachment=1,.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};

      VkSubpassDescription subpass =
      {
         .pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS,
         .colorAttachmentCount    = 1,
         .pColorAttachments       = &colorAttachmentRef,
         .pDepthStencilAttachment = &depthAttachmentRef,
      };

      VkSubpassDependency dependency =
      {
         .srcSubpass    = VK_SUBPASS_EXTERNAL,
         .dstSubpass    = 0,
         .srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
         .srcAccessMask = 0,
         .dstStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
         .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
      };

      VkAttachmentDescription attachments[] = {colorAttachment, depthAttachment};
      VkRenderPassCreateInfo renderPassInfo =
      {
         .sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
         .attachmentCount = sizeof(attachments)/sizeof(VkAttachmentDescription),
         .pAttachments    = attachments,
         .subpassCount    = 1,
         .pSubpasses      = &subpass,
         .dependencyCount = 1,
         .pDependencies   = &dependency,
      };
      if (vkCreateRenderPass(device,&renderPassInfo,NULL,&renderPass))
        Fatal("Failed to create render pass\n");
   }

   //  Create depth buffers
   CreateImage(swapChainExtent.width,swapChainExtent.height,depthFormat,VK_IMAGE_TILING_OPTIMAL,VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,&depthImage,&depthImageMemory);
   depthImageView = CreateImageView(depthImage,depthFormat,VK_IMAGE_ASPECT_DEPTH_BIT);

   //
   //  Create frame buffers
   //
   swapChainFramebuffers = (VkFramebuffer*)malloc(swapCount*sizeof(VkFramebuffer));
   for (int i=0;i<swapCount;i++)
   {
      VkImageView attachments[] = { swapChainImageViews[i],depthImageView };

      VkFramebufferCreateInfo framebufferInfo =
      {
         .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
         .renderPass = renderPass,
         .attachmentCount = sizeof(attachments)/sizeof(VkImageView),
         .pAttachments = attachments,
         .width = swapChainExtent.width,
         .height = swapChainExtent.height,
         .layers = 1,
      };

      if (vkCreateFramebuffer(device,&framebufferInfo,NULL,&swapChainFramebuffers[i]))
         Fatal("Failed to create framebuffer\n");
   }

}

//
//  Create Vulkan instance, physical and logical devices
//
void CreateDevice()
{
   //  Required device extensions
   const char* deviceExtensions[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

   //
   //  Create Vulkan instance
   //
   VkApplicationInfo appInfo =
   {
      .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pApplicationName   = "Vulkan Textured Cube",
      .applicationVersion = VK_MAKE_VERSION(1,0,0),
      .pEngineName        = "No Engine",
      .engineVersion      = VK_MAKE_VERSION(1,0,0),
      .apiVersion         = VK_API_VERSION_1_0,
   };

   uint32_t glfwExtensionCount = 0;
   const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

   VkInstanceCreateInfo createInfo =
   {
      .sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
      .pApplicationInfo        = &appInfo,
      .enabledExtensionCount   = glfwExtensionCount,
      .ppEnabledExtensionNames = glfwExtensions,
   };
   int ios = vkCreateInstance(&createInfo,NULL,&instance);
   if (ios) Fatal("Failed to create instance: %s\n",ErrString(ios));

   //  Create window surface
   ios = glfwCreateWindowSurface(instance,window,NULL,&surface);
   if (ios) Fatal("Failed to create window surface: %s\n",ErrString(ios));

   //
   //  Get available devices
   //
   uint32_t deviceCount=0;
   vkEnumeratePhysicalDevices(instance,&deviceCount,NULL);
   if (deviceCount==0) Fatal("Failed to find GPUs with Vulkan support\n");
   VkPhysicalDevice* devices = (VkPhysicalDevice*)malloc(deviceCount*sizeof(VkPhysicalDevice));
   if (!devices) Fatal("Failed to malloc %d VkPhysicalDevice\n",deviceCount);
   vkEnumeratePhysicalDevices(instance,&deviceCount,devices);

   //
   //  Select phyical device
   //
   physicalDevice = VK_NULL_HANDLE;
   for (int k=0;k<deviceCount && physicalDevice==VK_NULL_HANDLE;k++)
   {
      uint32_t queueFamilyCount = 0;
      vkGetPhysicalDeviceQueueFamilyProperties(devices[k],&queueFamilyCount,NULL);
      VkQueueFamilyProperties* queueFamilies = (VkQueueFamilyProperties*)malloc(queueFamilyCount*sizeof(VkQueueFamilyProperties));
      if (!queueFamilies) Fatal("Failed to malloc %d VkQueueFamilyProperties\n",queueFamilyCount);
      vkGetPhysicalDeviceQueueFamilyProperties(devices[k],&queueFamilyCount,queueFamilies);
      VkBool32 suitable = VK_FALSE;
      for (int i=0;i<queueFamilyCount && !suitable;i++)
      {
         VkBool32 presentSupport = VK_FALSE;
         vkGetPhysicalDeviceSurfaceSupportKHR(devices[k],i,surface,&presentSupport);
         VkPhysicalDeviceFeatures supportedFeatures;
         vkGetPhysicalDeviceFeatures(devices[k],&supportedFeatures);
         if (presentSupport && queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT && supportedFeatures.samplerAnisotropy)
         {
            suitable = VK_TRUE;
            presentFamily  = i;
            graphicsFamily = i;
         }
      }
      free(queueFamilies);

      //  Check that all required device extentions are supported
      if (suitable)
      {
         //  Get device extensions supported
         uint32_t extensionCount;
         vkEnumerateDeviceExtensionProperties(devices[k],NULL,&extensionCount,NULL);
         VkExtensionProperties* availableExtensions = (VkExtensionProperties*)malloc(extensionCount*sizeof(VkExtensionProperties));
         if (!availableExtensions) Fatal("Failed to malloc %d VkExtensionProperties\n",extensionCount);
         vkEnumerateDeviceExtensionProperties(devices[k],NULL,&extensionCount,availableExtensions);

         //  Check if device extentions match
         for (int k=0;k<sizeof(deviceExtensions)/sizeof(char*) && suitable;k++)
         {
            VkBool32 match = VK_FALSE;
            for (int i=0;i<extensionCount && !match;i++)
               if (!strcmp(deviceExtensions[k],availableExtensions[i].extensionName)) match = VK_TRUE;
            if (!match) suitable = VK_FALSE;
         }
         free(availableExtensions);
      }

      //  Get capabilities if device is suitable
      if (suitable)
      {
         //  Get device capabilities
         vkGetPhysicalDeviceSurfaceCapabilitiesKHR(devices[k],surface,&capabilities);
         //  Get formats
         if (formats) free(formats);
         vkGetPhysicalDeviceSurfaceFormatsKHR(devices[k],surface,&formatCount,NULL);
         if (formatCount)
         {
            formats = (VkSurfaceFormatKHR*)malloc(formatCount*sizeof(VkSurfaceFormatKHR));
            if (!formats) Fatal("Failed to malloc %d VkSurfaceFormatKHR\n",formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(devices[k],surface,&formatCount,formats);
         }
         else
            formats = NULL;
         //  Get presentation modes
         if (presentModes) free(presentModes);
         vkGetPhysicalDeviceSurfacePresentModesKHR(devices[k],surface,&presentModeCount,NULL);
         if (presentModeCount)
         {
            presentModes = (VkPresentModeKHR*)malloc(presentModeCount*sizeof(VkPresentModeKHR));
            if (!presentModes) Fatal("Failed to malloc %d VkPresentModeKHR\n",presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(devices[k],surface,&presentModeCount,presentModes);
         }
         else
            presentModes = NULL;
         //  Select device if formats and presentation modes are acceptable
         if (formats && presentModes)
            physicalDevice = devices[k];
      }
   }
   //  Stop if no GPU is found
   if (physicalDevice==VK_NULL_HANDLE)
      Fatal("Failed to find a suitable GPU\n");

   //
   //  Create logical device
   //
   int      infoCount = (graphicsFamily!=presentFamily) ? 2 : 1;
   float    queuePriority = 1;
   uint32_t uniqueQueueFamilies[] = {graphicsFamily,presentFamily};
   VkDeviceQueueCreateInfo queueCreateInfos[2];
   for (int k=0;k<infoCount;k++)
   {
      VkDeviceQueueCreateInfo queueCreateInfo =
      {
         .sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
         .queueFamilyIndex = uniqueQueueFamilies[k],
         .queueCount       = 1,
         .pQueuePriorities = &queuePriority,
      };
      queueCreateInfos[k] = queueCreateInfo;
   }
   VkPhysicalDeviceFeatures deviceFeatures = {.samplerAnisotropy=VK_TRUE};
   VkDeviceCreateInfo deviceInfo =
   {
      .sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
      .queueCreateInfoCount    = infoCount,
      .pQueueCreateInfos       = queueCreateInfos,
      .enabledExtensionCount   = sizeof(deviceExtensions)/sizeof(char*),
      .ppEnabledExtensionNames = deviceExtensions,
      .pEnabledFeatures        = &deviceFeatures,
   };
   if (vkCreateDevice(physicalDevice,&deviceInfo,NULL,&device))
      Fatal("Failed to create logical device %d\n");

   //  Get graphics and presentation queues
   vkGetDeviceQueue(device,graphicsFamily,0,&graphicsQueue);
   vkGetDeviceQueue(device,presentFamily,0,&presentQueue);

   //  Create command pool
   VkCommandPoolCreateInfo poolInfo =
   {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
      .queueFamilyIndex = graphicsFamily,
   };
   if (vkCreateCommandPool(device,&poolInfo,NULL,&commandPool))
       Fatal("Failed to create command pool\n");
}

//
//  Create graphics pipeline
//
void CreateGraphicsPipeline()
{
   //  Attributes for cube
   VkVertexInputBindingDescription bindingDescription =
   {
      .stride = sizeof(Vertex),
      .inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
   };
   //  Layout for xyz, rgb and st
   VkVertexInputAttributeDescription attributeDescriptions[] =
   {
      {.location=0, .format=VK_FORMAT_R32G32B32_SFLOAT, .offset=offsetof(Vertex,xyz) },
      {.location=1, .format=VK_FORMAT_R32G32B32_SFLOAT, .offset=offsetof(Vertex,nml) },
      {.location=2, .format=VK_FORMAT_R32G32B32_SFLOAT, .offset=offsetof(Vertex,rgb) },
      {.location=3, .format=VK_FORMAT_R32G32_SFLOAT   , .offset=offsetof(Vertex,st)  },
   };
   //  Set input state
   VkPipelineVertexInputStateCreateInfo vertexInputInfo =
   {
      .sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
      .vertexBindingDescriptionCount   = sizeof(bindingDescription)/sizeof(VkVertexInputBindingDescription),
      .pVertexBindingDescriptions      = &bindingDescription,
      .vertexAttributeDescriptionCount = sizeof(attributeDescriptions)/sizeof(VkVertexInputAttributeDescription),
      .pVertexAttributeDescriptions    = attributeDescriptions,
   };

   //  Create uniform buffers
   for (int k=0;k<NFRAMES;k++)
   {
      VkDeviceSize bufferSize = sizeof(UniformBufferObject);
      CreateBuffer(bufferSize,VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,&uniformBuffers[k],&uniformBuffersMemory[k]);
      vkMapMemory(device,uniformBuffersMemory[k],0,bufferSize,0,&uniformBuffersMapped[k]);
   }

   //  Uniform buffer layout
   VkDescriptorSetLayoutBinding uboLayoutBinding =
   {
      .binding = 0,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
      .pImmutableSamplers = NULL,
      .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
   };
   VkDescriptorSetLayoutBinding samplerLayoutBinding =
   {
      .binding = 1,
      .descriptorCount = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
      .pImmutableSamplers = NULL,
      .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
   };

   //  Create descriptor layout
   VkDescriptorSetLayoutBinding bindings[] = {uboLayoutBinding, samplerLayoutBinding};
   VkDescriptorSetLayoutCreateInfo layoutInfo =
   {
      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
      .bindingCount = sizeof(bindings)/sizeof(VkDescriptorSetLayoutBinding),
      .pBindings = bindings,
   };
   if (vkCreateDescriptorSetLayout(device,&layoutInfo,NULL,&descriptorSetLayout))
      Fatal("Failed to create descriptor set layout\n");

   //  Pipeline layout
   VkPipelineLayoutCreateInfo pipelineLayoutInfo =
   {
      .sType          = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
      .setLayoutCount = 1,
      .pSetLayouts    = &descriptorSetLayout,
   };
   if (vkCreatePipelineLayout(device,&pipelineLayoutInfo,NULL,&pipelineLayout))
      Fatal("Failed to create pipeline layout\n");

   //  Create descriptor pool
   VkDescriptorPoolSize poolSizes[] =
   {
      {.type=VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER        , .descriptorCount=NFRAMES},
      {.type=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, .descriptorCount=NFRAMES},
   };

   VkDescriptorPoolCreateInfo dsPoolInfo =
   {
      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
      .poolSizeCount = sizeof(poolSizes)/sizeof(VkDescriptorPoolSize),
      .pPoolSizes = poolSizes,
      .maxSets = NFRAMES,
   };
   if (vkCreateDescriptorPool(device,&dsPoolInfo,NULL,&descriptorPool))
      Fatal("Failed to create descriptor pool\n");

   //  Create descriptor sets
   VkDescriptorSetLayout layouts[NFRAMES];
   for (int k=0;k<NFRAMES;k++)
      layouts[k] =  descriptorSetLayout;
   VkDescriptorSetAllocateInfo dsAllocInfo =
   {
      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
      .descriptorPool = descriptorPool,
      .descriptorSetCount = NFRAMES,
      .pSetLayouts = layouts,
   };
   if (vkAllocateDescriptorSets(device,&dsAllocInfo,descriptorSets))
      Fatal("Failed to allocate descriptor sets\n");
   //  Set descriptors for each frame
   for (int k=0;k<NFRAMES;k++)
   {
      VkDescriptorBufferInfo bufferInfo =
      {
         .buffer = uniformBuffers[k],
         .offset = 0,
         .range = sizeof(UniformBufferObject),
      };
      VkDescriptorImageInfo imageInfo =
      {
         .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
         .imageView = textureImageView,
         .sampler = textureSampler,
      };

      VkWriteDescriptorSet descriptorWrites[] =
      {
         {
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .dstSet = descriptorSets[k],
            .dstBinding = 0,
            .dstArrayElement = 0,
            .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
            .descriptorCount = 1,
            .pBufferInfo = &bufferInfo,
         },
         {
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .dstSet = descriptorSets[k],
            .dstBinding = 1,
            .dstArrayElement = 0,
            .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
            .descriptorCount = 1,
            .pImageInfo = &imageInfo,
         },
      };

      vkUpdateDescriptorSets(device,sizeof(descriptorWrites)/sizeof(VkWriteDescriptorSet),descriptorWrites,0,NULL);
   }

   //  Select TRIANGLE LIST
   VkPipelineInputAssemblyStateCreateInfo inputAssembly =
   {
      .sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
      .topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
      .primitiveRestartEnable = VK_FALSE,
   };

   //  Enable CULL FACE
   VkPipelineRasterizationStateCreateInfo rasterizer =
   {
      .sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
      .depthClampEnable        = VK_FALSE,
      .rasterizerDiscardEnable = VK_FALSE,
      .polygonMode             = VK_POLYGON_MODE_FILL,
      .lineWidth               = 1,
      .cullMode                = VK_CULL_MODE_BACK_BIT,
      .frontFace               = VK_FRONT_FACE_COUNTER_CLOCKWISE,
      .depthBiasEnable         = VK_FALSE,
   };

   //  Enable Z-buffer
   VkPipelineDepthStencilStateCreateInfo depthStencil =
   {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
      .depthTestEnable = VK_TRUE,
      .depthWriteEnable = VK_TRUE,
      .depthCompareOp = VK_COMPARE_OP_LESS,
      .depthBoundsTestEnable = VK_FALSE,
      .stencilTestEnable = VK_FALSE,
   };

   //  Disable multisampling
   VkPipelineMultisampleStateCreateInfo multisampling =
   {
      .sType                = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
      .sampleShadingEnable  = VK_FALSE,
      .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
   };

   //  Disable blending
   VkPipelineColorBlendAttachmentState colorBlendAttachment =
   {
      .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
      .blendEnable    = VK_FALSE,
   };

   //  Blend function copy
   VkPipelineColorBlendStateCreateInfo colorBlending =
   {
      .sType             = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
      .logicOpEnable     = VK_FALSE,
      .logicOp           = VK_LOGIC_OP_COPY,
      .attachmentCount   = 1,
      .pAttachments      = &colorBlendAttachment,
      .blendConstants[0] = 0,
      .blendConstants[1] = 0,
      .blendConstants[2] = 0,
      .blendConstants[3] = 0,
   };

   //  Enable viewport and scissors test
   VkPipelineViewportStateCreateInfo viewportState =
   {
      .sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
      .viewportCount = 1,
      .scissorCount  = 1,
   };

   //  Allow viewport and scissors to change dynamically
   VkDynamicState dynamicStates[] = {VK_DYNAMIC_STATE_VIEWPORT,VK_DYNAMIC_STATE_SCISSOR};
   VkPipelineDynamicStateCreateInfo dynamicState =
   {
      .sType             = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
      .dynamicStateCount = sizeof(dynamicStates)/sizeof(VkDynamicState),
      .pDynamicStates    = dynamicStates,
   };

   //  Vertex shader module
   VkShaderModule vertShaderModule = CreateShaderModule("vert.spv");
   VkPipelineShaderStageCreateInfo vertShaderStageInfo =
   {
      .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage  = VK_SHADER_STAGE_VERTEX_BIT,
      .module = vertShaderModule,
      .pName  = "main",
   };

   //  Fragment shader module
   VkShaderModule fragShaderModule = CreateShaderModule("frag.spv");
   VkPipelineShaderStageCreateInfo fragShaderStageInfo =
   {
      .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage  = VK_SHADER_STAGE_FRAGMENT_BIT,
      .module = fragShaderModule,
      .pName  = "main",
   };

   //  Create graphics pipeline
   VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo,fragShaderStageInfo};
   VkGraphicsPipelineCreateInfo pipelineInfo =
   {
      .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
      .stageCount = 2,
      .pStages = shaderStages,
      .pVertexInputState = &vertexInputInfo,
      .pInputAssemblyState = &inputAssembly,
      .pViewportState      = &viewportState,
      .pRasterizationState = &rasterizer,
      .pDepthStencilState  = &depthStencil,
      .pMultisampleState   = &multisampling,
      .pColorBlendState    = &colorBlending,
      .pDynamicState       = &dynamicState,
      .layout              = pipelineLayout,
      .renderPass          = renderPass,
      .subpass             = 0,
      .basePipelineHandle  = VK_NULL_HANDLE,
   };
   if (vkCreateGraphicsPipelines(device,VK_NULL_HANDLE,1,&pipelineInfo,NULL,&graphicsPipeline))
      Fatal("failed to create graphics pipeline\n");

   //  Delete shader modules
   vkDestroyShaderModule(device,fragShaderModule,NULL);
   vkDestroyShaderModule(device,vertShaderModule,NULL);
}

//
//  Start one time commands
//
VkCommandBuffer BeginSingleTimeCommands()
{
   VkCommandBufferAllocateInfo allocInfo =
   {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandPool = commandPool,
      .commandBufferCount = 1,
   };

   VkCommandBuffer commandBuffer;
   vkAllocateCommandBuffers(device,&allocInfo,&commandBuffer);

   VkCommandBufferBeginInfo beginInfo =
   {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
      .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
   };
   vkBeginCommandBuffer(commandBuffer,&beginInfo);

   return commandBuffer;
}

//
//  End one time commands
//
void EndSingleTimeCommands(VkCommandBuffer commandBuffer)
{
   vkEndCommandBuffer(commandBuffer);

   VkSubmitInfo submitInfo =
   {
      .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
      .commandBufferCount = 1,
      .pCommandBuffers = &commandBuffer,
   };
   vkQueueSubmit(graphicsQueue,1,&submitInfo,VK_NULL_HANDLE);
   vkQueueWaitIdle(graphicsQueue);
   vkFreeCommandBuffers(device,commandPool,1,&commandBuffer);
}

//
//  Transition image layout
//
void TransitionImageLayout(VkImage image,VkFormat format,VkImageLayout oldLayout,VkImageLayout newLayout)
{
   VkCommandBuffer commandBuffer = BeginSingleTimeCommands();

   VkImageMemoryBarrier barrier =
   {
      .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
      .oldLayout = oldLayout,
      .newLayout = newLayout,
      .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      .image = image,
      .subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
      .subresourceRange.baseMipLevel = 0,
      .subresourceRange.levelCount = 1,
      .subresourceRange.baseArrayLayer = 0,
      .subresourceRange.layerCount = 1,
   };

   VkPipelineStageFlags sourceStage=0;
   VkPipelineStageFlags destinationStage=0;
   if (oldLayout==VK_IMAGE_LAYOUT_UNDEFINED && newLayout==VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
   {
      barrier.srcAccessMask = 0;
      barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

      sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
      destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
   }
   else if (oldLayout==VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout==VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
   {
      barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
      barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

      sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
      destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
   }
   else
      Fatal("Unsupported layout transition\n");

   vkCmdPipelineBarrier(commandBuffer,sourceStage,destinationStage,0,0,NULL,0,NULL,1,&barrier);

   EndSingleTimeCommands(commandBuffer);
}

//
//  Reverse n bytes
//
static void Reverse(void* x,const int n)
{
   char* ch = (char*)x;
   for (int k=0;k<n/2;k++)
   {
      char tmp = ch[k];
      ch[k] = ch[n-1-k];
      ch[n-1-k] = tmp;
   }
}

//
//  Load texture from BMP file
//
void CreateTextureImage(const char* file)
{
   //  Open file
   FILE* f = fopen(file,"r");
   if (!f) Fatal("Cannot open file %s\n",file);
   //  Check image magic
   unsigned short magic;
   if (fread(&magic,2,1,f)!=1) Fatal("Cannot read magic from %s\n",file);
   if (magic!=0x4D42 && magic!=0x424D) Fatal("Image magic not BMP in %s\n",file);
   //  Read header
   unsigned int dx,dy,off,k; // Image dimensions, offset and compression
   unsigned short nbp,bpp;   // Planes and bits per pixel
   if (fseek(f,8,SEEK_CUR) || fread(&off,4,1,f)!=1 ||
       fseek(f,4,SEEK_CUR) || fread(&dx,4,1,f)!=1 || fread(&dy,4,1,f)!=1 ||
       fread(&nbp,2,1,f)!=1 || fread(&bpp,2,1,f)!=1 || fread(&k,4,1,f)!=1)
     Fatal("Cannot read header from %s\n",file);
   //  Reverse bytes on big endian hardware (detected by backwards magic)
   if (magic==0x424D)
   {
      Reverse(&off,4);
      Reverse(&dx,4);
      Reverse(&dy,4);
      Reverse(&nbp,2);
      Reverse(&bpp,2);
      Reverse(&k,4);
   }
   //  Get physical device properties
   VkPhysicalDeviceProperties properties;
   vkGetPhysicalDeviceProperties(physicalDevice,&properties);
   unsigned int max=properties.limits.maxImageDimension2D;
   //  Check image parameters
   if (dx<1 || dx>max) Fatal("%s image width %d out of range 1-%d\n",file,dx,max);
   if (dy<1 || dy>max) Fatal("%s image height %d out of range 1-%d\n",file,dy,max);
   if (nbp!=1)  Fatal("%s bit planes is not 1: %d\n",file,nbp);
   if (bpp!=24) Fatal("%s bits per pixel is not 24: %d\n",file,bpp);
   if (k!=0)    Fatal("%s compressed files not supported\n",file);

   //  Allocate image memory
   VkDeviceSize imageSize = 4*dx*dy;
   unsigned char* image = (unsigned char*) malloc(imageSize);
   if (!image) Fatal("Cannot allocate %d bytes of memory for image %s\n",imageSize,file);

   //  Seek to and read image
   if (fseek(f,off,SEEK_SET) || fread(image,3*dx*dy,1,f)!=1) Fatal("Error reading data from image %s\n",file);
   fclose(f);
   //  Map BGR to RGBA (RGBA is better supported)
   for (int i=dx*dy-1;i>=0;i--)
   {
      unsigned char R = image[3*i+2];
      unsigned char G = image[3*i+1];
      unsigned char B = image[3*i+0];
      image[4*i+0] = R;
      image[4*i+1] = G;
      image[4*i+2] = B;
      image[4*i+3] = 255;
   }

   //  Create staging buffer
   VkBuffer stagingBuffer;
   VkDeviceMemory stagingBufferMemory;
   CreateBuffer(imageSize,VK_BUFFER_USAGE_TRANSFER_SRC_BIT,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT|VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,&stagingBuffer,&stagingBufferMemory);
   //  Copy image to buffer
   void* data;
   vkMapMemory(device,stagingBufferMemory,0,imageSize,0,&data);
   memcpy(data,image,imageSize);
   vkUnmapMemory(device,stagingBufferMemory);
   free(image);
   //  Create Image
   CreateImage(dx,dy,VK_FORMAT_R8G8B8A8_SRGB,VK_IMAGE_TILING_OPTIMAL,VK_IMAGE_USAGE_TRANSFER_DST_BIT|VK_IMAGE_USAGE_SAMPLED_BIT,VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,&textureImage,&textureImageMemory);
   //  Transfer buffer to image
   TransitionImageLayout(textureImage,VK_FORMAT_R8G8B8A8_SRGB,VK_IMAGE_LAYOUT_UNDEFINED,VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
   VkCommandBuffer commandBuffer = BeginSingleTimeCommands();
   VkBufferImageCopy region =
   {
      .bufferOffset = 0,
      .bufferRowLength = 0,
      .bufferImageHeight = 0,
      .imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
      .imageSubresource.mipLevel = 0,
      .imageSubresource.baseArrayLayer = 0,
      .imageSubresource.layerCount = 1,
      .imageOffset = {0,0,0},
      .imageExtent = {dx,dy,1},
   };
   vkCmdCopyBufferToImage(commandBuffer,stagingBuffer,textureImage,VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,1,&region);
   EndSingleTimeCommands(commandBuffer);
   TransitionImageLayout(textureImage,VK_FORMAT_R8G8B8A8_SRGB,VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

   //  Destroy staging buffer
   vkDestroyBuffer(device,stagingBuffer,NULL);
   vkFreeMemory(device,stagingBufferMemory,NULL);

   //  Create texture sampler
   VkSamplerCreateInfo samplerInfo =
   {
      .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
      .magFilter = VK_FILTER_LINEAR,
      .minFilter = VK_FILTER_LINEAR,
      .addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .anisotropyEnable = VK_TRUE,
      .maxAnisotropy = properties.limits.maxSamplerAnisotropy,
      .borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
      .unnormalizedCoordinates = VK_FALSE,
      .compareEnable = VK_FALSE,
      .compareOp = VK_COMPARE_OP_ALWAYS,
      .mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR,
   };
   if (vkCreateSampler(device,&samplerInfo,NULL,&textureSampler))
      Fatal("Failed to create texture sampler\n");

   //  Create Image View
   textureImageView = CreateImageView(textureImage,VK_FORMAT_R8G8B8A8_SRGB,VK_IMAGE_ASPECT_COLOR_BIT);
}

//
//  Create command pool, buffer and semaphores
//
void CreateCommandSync()
{
   //
   //  Create command buffer
   //
   VkCommandBufferAllocateInfo allocInfo =
   {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
      .commandPool = commandPool,
      .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
      .commandBufferCount = NFRAMES,
   };
   if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers))
      Fatal("Failed to allocate command buffers\n");

   //
   //  Create synchronization objects
   //
   VkSemaphoreCreateInfo semaphoreInfo = {.sType=VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
   VkFenceCreateInfo fenceInfo =
   {
      .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
      .flags = VK_FENCE_CREATE_SIGNALED_BIT,
   };
   for (int k=0;k<NFRAMES;k++)
   {
      if (vkCreateSemaphore(device,&semaphoreInfo,NULL,&imageAvailableSemaphores[k]) ||
          vkCreateSemaphore(device,&semaphoreInfo,NULL,&renderFinishedSemaphores[k]) ||
          vkCreateFence(device,&fenceInfo,NULL,&inFlightFences[k]))
            Fatal("Failed to create synchronization objects for a frame\n");
   }
}

//
//  Record command buffer
//
void RecordCommandBuffer(VkCommandBuffer commandBuffer,uint32_t imageIndex)
{
   //  Begin command buffer
   VkCommandBufferBeginInfo beginInfo = {.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
   if (vkBeginCommandBuffer(commandBuffer, &beginInfo))
      Fatal("Failed to begin recording command buffer\n");

   //  Begin render pass
   VkOffset2D origin = {0,0};
   VkRenderPassBeginInfo renderPassInfo =
   {
      .sType             = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
      .renderPass        = renderPass,
      .framebuffer       = swapChainFramebuffers[imageIndex],
      .renderArea.offset = origin,
      .renderArea.extent = swapChainExtent,
   };

   //  Begin render pass by clearing the screen and Z-buffer
   VkClearValue clearValues[] =
   {
      {.color={{0.0,0.0,0.0,1.0}}},
      {.depthStencil={1.0,0}},
   };
   renderPassInfo.clearValueCount = sizeof(clearValues)/sizeof(VkClearValue);
   renderPassInfo.pClearValues    = clearValues;
   vkCmdBeginRenderPass(commandBuffer,&renderPassInfo,VK_SUBPASS_CONTENTS_INLINE);

   //  Bind the graphics pipeline
   vkCmdBindPipeline(commandBuffer,VK_PIPELINE_BIND_POINT_GRAPHICS,graphicsPipeline);

   //  Viewport is the entire window
   VkViewport viewport =
   {
      .x        = 0,
      .y        = 0,
      .width    = swapChainExtent.width,
      .height   = swapChainExtent.height,
      .minDepth = 0,
      .maxDepth = 1,
   };
   vkCmdSetViewport(commandBuffer,0,1,&viewport);

   //  Scissor is entire window
   VkRect2D scissor =
   {
      .offset = origin,
      .extent = swapChainExtent,
   };
   vkCmdSetScissor(commandBuffer,0,1,&scissor);

   //  Bind vertex buffer and uniform buffer
   VkBuffer vertexBuffers[] = {vertexBuffer};
   VkDeviceSize offsets[] = {0};
   vkCmdBindVertexBuffers(commandBuffer,0,1,vertexBuffers,offsets);
   vkCmdBindDescriptorSets(commandBuffer,VK_PIPELINE_BIND_POINT_GRAPHICS,pipelineLayout,0,1,&descriptorSets[currentFrame],0,NULL);

   //  Render the object
   vkCmdDraw(commandBuffer,sizeof(vertices)/sizeof(Vertex),1,0,0);

   //  End of render pass
   vkCmdEndRenderPass(commandBuffer);

   //  End of commands
   if (vkEndCommandBuffer(commandBuffer))
      Fatal("Failed to record command buffer\n");
}

//
//  Draw frame
//
void display()
{
   //  Wait for previous operations to complete
   vkWaitForFences(device,1,&inFlightFences[currentFrame],VK_TRUE,UINT64_MAX);

   //  On resize, update the swapchain
   uint32_t imageIndex;
   VkResult result = vkAcquireNextImageKHR(device,swapChain,UINT64_MAX,imageAvailableSemaphores[currentFrame],VK_NULL_HANDLE,&imageIndex);
   if (result==VK_ERROR_OUT_OF_DATE_KHR)
   {
      CreateSwapChain(0);
      return;
   }
   else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
      Fatal("Failed to acquire swap chain image\n");

   //  Update uniforms
   UniformBufferObject ubo;
   //  Model matrix
   mat4identity(ubo.model);
   //  View matrix
   mat4identity(ubo.view);
   if (proj)
   {
      double Ex = -2*dim*Sin(th)*Cos(-ph);
      double Ey = +2*dim        *Sin(-ph);
      double Ez = +2*dim*Cos(th)*Cos(-ph);
      mat4lookAt(ubo.view,Ex,Ey,Ez , 0,0,0 , 0,Cos(-ph),0);
   }
   else
   {
      mat4rotate(ubo.view,-ph,1,0,0);
      mat4rotate(ubo.view,th,0,1,0);
   }
   //  Projection matrix
   float asp=(float)swapChainExtent.width/swapChainExtent.height;
   mat4identity(ubo.proj);
   if (proj)
      mat4perspective(ubo.proj,fov,asp,dim/16,16*dim);
   else
      mat4ortho(ubo.proj,-asp*dim,+asp*dim,-dim,+dim,-dim,+dim);
   //  Normal matrix
   float MV[16];
   mat4copy(MV,ubo.view);
   mat4multMatrix(MV,ubo.model);
   mat4normalMatrix(ubo.view,ubo.norm);

   //  Set light position based on time
   if (move) zh = fmod(90*glfwGetTime(),360.0);
   ubo.pos.x = 4*Cos(zh);
   ubo.pos.y = Ylight;
   ubo.pos.z = 4*Sin(zh);
   ubo.pos.w = 1;
   //  Set colors
   vec4 grey  = {0.3,0.3,0.3,1};
   vec4 white = {1,1,1,1};
   ubo.Ca = grey;
   ubo.Cd = white;
   ubo.Cs = white;
   ubo.Ks = white;
   ubo.Ns = 16;

   //  Copy uniform data to buffer
   memcpy(uniformBuffersMapped[currentFrame],&ubo,sizeof(ubo));

   //  Clear fences
   vkResetFences(device,1,&inFlightFences[currentFrame]);

   //  Flush command buffer and recreate
   vkResetCommandBuffer(commandBuffers[currentFrame], /*VkCommandBufferResetFlagBits*/ 0);
   RecordCommandBuffer(commandBuffers[currentFrame],imageIndex);

   //  Set semaphores
   VkSemaphore waitSemaphores[] = {imageAvailableSemaphores[currentFrame]};
   VkSemaphore signalSemaphores[] = {renderFinishedSemaphores[currentFrame]};
   VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
   VkSubmitInfo submitInfo =
   {
      .sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO,
      .waitSemaphoreCount = 1,
      .pWaitSemaphores    = waitSemaphores,
      .pWaitDstStageMask  = waitStages,
      .commandBufferCount = 1,
      .pCommandBuffers    = &commandBuffers[currentFrame],
      .signalSemaphoreCount = 1,
      .pSignalSemaphores = signalSemaphores,
   };
   int ios = vkQueueSubmit(graphicsQueue,1,&submitInfo,inFlightFences[currentFrame]);
   if (ios) Fatal("Failed to submit draw command buffer: %s\n",ErrString(ios));

   //  Set presentation queue
   VkSwapchainKHR swapChains[] = {swapChain};
   VkPresentInfoKHR presentInfo =
   {
      .sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
      .waitSemaphoreCount = 1,
      .pWaitSemaphores    = signalSemaphores,
      .swapchainCount     = 1,
      .pSwapchains        = swapChains,
      .pImageIndices      = &imageIndex,
   };
   result = vkQueuePresentKHR(presentQueue,&presentInfo);
   if (result==VK_ERROR_OUT_OF_DATE_KHR || result==VK_SUBOPTIMAL_KHR || framebufferResized)
   {
      framebufferResized = 0;
      CreateSwapChain(0);
   }
   else if (result)
      Fatal("Failed to present swap chain image\n");

   //  Switch frames
   currentFrame = (currentFrame+1) % NFRAMES;
}

//
//  Close vulkan
//
void DestroyVulkan()
{
   //  Destroy semaphores and commands
   vkDeviceWaitIdle(device);
   for (int k=0;k<NFRAMES;k++)
   {
      vkDestroySemaphore(device,renderFinishedSemaphores[k],NULL);
      vkDestroySemaphore(device,imageAvailableSemaphores[k],NULL);
      vkDestroyFence(device,inFlightFences[k],NULL);
   }
   vkDestroyCommandPool(device,commandPool,NULL);

   //  Destroy swapchain, images and framebuffers
   DestroySwapChain();

   //  Destroy Texture
   vkDestroyImage(device,textureImage,NULL);
   vkFreeMemory(device,textureImageMemory,NULL);
   vkDestroySampler(device,textureSampler,NULL);
   vkDestroyImageView(device,textureImageView,NULL);

   //  Destroy graphics pipeline
   vkDestroyPipeline(device,graphicsPipeline,NULL);
   vkDestroyPipelineLayout(device,pipelineLayout,NULL);
   vkDestroyRenderPass(device,renderPass,NULL);

   //  Destroy device, surface and main instance
   vkDestroyDevice(device,NULL);
   vkDestroySurfaceKHR(instance,surface,NULL);
   vkDestroyInstance(instance,NULL);
}

//
//  Key pressed callback
//
void key(GLFWwindow* window,int key,int scancode,int action,int mods)
{
   //  Discard key releases (keeps PRESS and REPEAT)
   if (action==GLFW_RELEASE) return;

   //  Exit on ESC
   if (key == GLFW_KEY_ESCAPE)
      glfwSetWindowShouldClose(window,1);
   //  Right arrow key - increase angle by 5 degrees
   else if (key == GLFW_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLFW_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLFW_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLFW_KEY_DOWN)
      ph -= 5;
   //  Toggle projection type
   else if (key == GLFW_KEY_P)
      proj = 1-proj;
   //  Light movement
   else if (key == GLFW_KEY_M)
      move = !move;
   //  Light elevation
   else if (key == GLFW_KEY_KP_ADD)
      Ylight += 0.1;
   else if (key == GLFW_KEY_KP_SUBTRACT)
      Ylight -= 0.1;
   //  Light position
   else if (key==GLFW_KEY_LEFT_BRACKET)
      zh += 1;
   else if (key==GLFW_KEY_RIGHT_BRACKET)
      zh -= 1;
}

//
//  Callback for window resized
//
static void resize(GLFWwindow* window,int width,int height)
{
   framebufferResized = 1;
}

//
//  Main program
//
int main()
{
   //  Initialize GLFW
   glfwInit();
   glfwWindowHint(GLFW_CLIENT_API,GLFW_NO_API);
   glfwWindowHint(GLFW_RESIZABLE,GLFW_TRUE);
   window = glfwCreateWindow(600,600,"Vulkan",NULL,NULL);
   //  Set callbacks for window resize and keyboard
   glfwSetFramebufferSizeCallback(window,resize);
   glfwSetKeyCallback(window,key);
   mat4vulkan(1);

   //  Create instance, physical and logical devices
   CreateDevice();
   //  Create the swapchain, image and framebuffers
   CreateSwapChain(1);
   //  Load texture
   CreateTextureImage("pi.bmp");
   //  Create graphics pipeline
   CreateGraphicsPipeline();
   //  Create command pool, buffer and semaphores
   CreateCommandSync();
   //  Create vertex buffer
   CreateVertexBuffer();

   //  Main loop
   while (!glfwWindowShouldClose(window))
   {
      display();
      glfwPollEvents();
   }
 
   //  Cleanup vulkan and GLFW
   DestroyVulkan();
   glfwDestroyWindow(window);
   glfwTerminate();
   return 0;
}
