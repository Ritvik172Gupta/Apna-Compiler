const editor = ace.edit("editor");
editor.setTheme("ace/theme/monokai");
editor.session.setMode("ace/mode/c_cpp");

document.getElementById('runBtn').addEventListener('click', async () => {
  const code = editor.getValue();

  try {
    const response = await fetch('/run', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({ code: code })
    });

    const result = await response.json();

    // Show the result output — including error messages
    document.getElementById('output').textContent =
      result.output && result.output.trim() !== ""
        ? "Output:\n" + result.output
        : "⚠️ No output returned.";
  } catch (error) {
    // Catch network or fetch errors
    document.getElementById('output').textContent = "❌ Error contacting server:\n" + error.message;
  }
});
